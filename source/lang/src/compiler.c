#include <stdio.h>
#include <stdlib.h>

#include "chunk.h"
#include "common.h"
#include "compiler.h"
#include "scanner.h"
#include "value.h"

#ifdef DEBUG_PRINT_CODE
#include "debug.h"
#endif

/**
 * @brief Parser struct to hold the current and previous parser
 *
 */
typedef struct {
    Token current;
    Token previous;

    bool hadError;  // if the parser encountered an error during parsing
    bool panicMode; // set panicMode to unwind out of the parser code
} Parser;

typedef enum {
    PREC_NONE,
    PREC_ASSIGNMENT,  // =
    PREC_OR,          // or
    PREC_AND,         // and
    PREC_EQUALITY,    // == !=
    PREC_COMPARISON,  // < > <= >=
    PREC_TERM,        // + -
    PREC_FACTOR,      // * / %
    PREC_UNARY,       // ! -
    PREC_CALL,        // . ()
    PREC_PRIMARY
} Precedence;

/**
 * @brief ParseFn is a simple typedef for a function with no args and no return
 *
 */
typedef void (*ParseFn)(bool canAssign);

/**
 * @brief Wrapper for a single row in the parser table
 *
 */
typedef struct {
    ParseFn prefix;
    ParseFn infix;
    Precedence precedence;
} ParseRule;

/**
 * @brief Struct for local variable
 *
 */
typedef struct {
    Token name;
    int depth; // Depth of local variable
} Local;

/**
 * @brief Struct for holding the list of local variables
 *
 */
typedef struct {
    Local locals[UINT8_COUNT];
    int localCount; // The number of local variables
    int scopeDepth; // The depth of the scope (0 for global)
} Compiler;

Parser parser;

// global compilers bad for multithreading
Compiler* current = NULL; 
Chunk* compilingChunk;

/**
 * @brief Method to return the current chunk in compilation
 * 
 * @return Chunk* The pointer to the current chunk in compilation
 */
static Chunk* currentChunk() {
    return compilingChunk;
}

/**
 * @brief Method to handle an error and set out an error message
 * @param token Pointer to token with the error
 * @param message Error message
 *
 */
static void errorAt(Token* token, const char* message) {
    if (parser.panicMode) return;
    parser.panicMode = true;
    fprintf(stderr, "[line %d] Error", token->line);

    if (token->type==TOKEN_EOF) {
        fprintf(stderr, " at end");
    } else if (token->type == TOKEN_ERROR) {
        // pass
    } else {
        fprintf(stderr, " at '%.*s'", token->length, token->start);
    }
    fprintf(stderr, ": %s\n", message);
    parser.hadError = true;
}

/**
 * @brief Method to handle an error that happened at a token we just consumed
 * @param message Error message
 *
 */
static void error(const char* message) {
    errorAt(&parser.previous, message);
}

/**
 * @brief Method to handle a parser error and set out an error message.
 * @param message Error message
 *
 */
static void errorAtCurrent(const char* message) {
    errorAt(&parser.current, message);
}

/**
 * @brief Method to advance in a stream of tokens
 *
 */
static void advance() {
    parser.previous = parser.current;

    for (;;) {
        parser.current = scanToken();
        if (parser.current.type != TOKEN_ERROR) break;

        errorAtCurrent(parser.current.start);
    }
}

/**
 * @brief Method to advance a token, validates it for an expected type, and 
 * reports an error if it doesn't encounter the correct type
 * @param type The expected token type of the current token.
 * @param message Error message to be emitted
 * 
 */
static void consume(TokenType type, const char* message) {
    if (parser.current.type==type) {
        advance();
        return;
    }

    errorAtCurrent(message);
}

/**
 * @brief Helper method to check if the current type is of a certain type
 *
 * @param type The type to match 
 * @return True if the types match
 */
static bool check(TokenType type) {
    return parser.current.type == type;
}

/**
 * @brief Method to check the current type going through the parser
 *
 * @param type The type to match
 * @return True if the types match
 */
static bool match(TokenType type) {
    if (!check(type)) return false;
    advance();
    return true;
}

/**
 * @brief Method to append a single byte to the chunk
 * @param byte Byte to write
 *
 */
static void emitByte(uint8_t byte) {
    writeChunk(currentChunk(), byte, parser.previous.line);
}

/**
 * @brief Method to emit two bytes
 * @param byte1 Byte to write to chunk
 * @param byte2 Byte to write to chunk
 *
 */
static void emitBytes(uint8_t byte1, uint8_t byte2) {
    emitByte(byte1);
    emitByte(byte2);
}

/**
 * @brief Method to write OP_RETURN to the current chunk
 *
 */
static void emitReturn() {
    emitByte(OP_RETURN);
}

/**
 * @brief Method to insert an entry into the constant table
 * @param value Value to insert
 *
 */
static uint8_t makeConstant(Value value) {
    int constant = addConstant(currentChunk(), value);

    // store up to 256 constants in a chunk. Needs to be expanded
    if (constant > UINT8_MAX) {
        error("Too many constants in one chunk.");
        return 0;
    }

    return (uint8_t)constant;
}

/**
 * @brief Method to write a constant to the current chunk
 * @param value Value to write to current chunk
 *
 */
static void emitConstant(Value value) {
    emitBytes(OP_CONSTANT, makeConstant(value));
}

/**
 * @brief Constructor for the compiler struct. Zero initializes the values for
 * the compiler
 *
 * @param compiler The pointer to the compiler to be initialized
 */
static void initCompiler(Compiler* compiler) {
    compiler->localCount = 0;
    compiler->scopeDepth = 0;
    current = compiler;
}

/**
 * @brief Method to end the compiler by writing the return signal
 *
 */
static void endCompiler() {
    emitReturn();
#ifdef DEBUG_PRINT_CODE
    if (!parser.hadError) {
        disassembleChunk( currentChunk(), "code");
    }
#endif
}

/**
 * @brief Method to "go down" a single scope.
 *
 */
static void beginScope() {
    current->scopeDepth++;
}

/**
 * @brief Method to "go up" a single scope.
 * 
 */
static void endScope() {
    current->scopeDepth--;
}

/* Wrapper function declarations */
static void expression();
static void statement();
static void declaration();
static ParseRule* getRule(TokenType type);
static void parsePrecedence(Precedence precedence);
static uint8_t identifierConstant(Token* name);

/**
 * @brief Method to handle binary operations
 *
 */
static void binary(bool canAssign) {
    TokenType operatorType = parser.previous.type;
    ParseRule* rule = getRule(operatorType);
    parsePrecedence( (Precedence)(rule->precedence + 1) );

    switch (operatorType) {
        // logic oper
        case TOKEN_BANG_EQUAL:    emitBytes(OP_EQUAL, OP_NOT); break;
        case TOKEN_EQUAL_EQUAL:   emitByte(OP_EQUAL); break;
        case TOKEN_GREATER:       emitByte(OP_GREATER); break;
        case TOKEN_GREATER_EQUAL: emitBytes(OP_LESS, OP_NOT); break;
        case TOKEN_LESS:          emitByte(OP_LESS); break;
        case TOKEN_LESS_EQUAL:    emitBytes(OP_GREATER, OP_NOT); break;

        // math oper
        case TOKEN_PLUS:          emitByte(OP_ADD); break;
        case TOKEN_MINUS:         emitByte(OP_SUBTRACT); break;
        case TOKEN_STAR:          emitByte(OP_MULTIPLY); break;
        case TOKEN_SLASH:         emitByte(OP_DIVIDE); break;
        case TOKEN_MOD:           emitByte(OP_MOD); break;

        // unreachable
        default: return;
    }
}

/**
 *
 *
 */
static void literal(bool canAssign) {
    switch (parser.previous.type) {
        case TOKEN_FALSE:  emitByte(OP_FALSE); break;
        case TOKEN_NULL:   emitByte(OP_NULL); break;
        case TOKEN_TRUE:   emitByte(OP_TRUE); break;

        // unreachable
        default: return;
    }
}

/**
 * @brief Method to handle grouping by parenthesis. Recursively call
 * expression() to handle expressions within the parenthesis
 *
 */
static void grouping(bool canAssign) {
    expression(); // takes care of generating bytecode inside the parenthesis
    consume(TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
}

/**
 * @brief Method to convert a parsed string to a number
 *
 */
static void number(bool canAssign) {
    double value = strtod(parser.previous.start, NULL);
    emitConstant(NUMBER_VAL(value));
}

/**
 * @brief Method to convert a parsed string into string value
 *
 */
static void string(bool canAssign) {
    emitConstant( OBJ_VAL(copyString(parser.previous.start + 1,
                                     parser.previous.length -2)) );
}

/**
 * @brief TODO add comment here
 *
 * @param name 
 */
static void namedVariable(Token name, bool canAssign) {
    uint8_t arg = identifierConstant(&name);
    if (canAssign && match(TOKEN_EQUAL)) {
        expression();
        emitBytes(OP_SET_GLOBAL, arg);
    } else {
        emitBytes(OP_GET_GLOBAL, arg);
    }
}

/**
 * @brief Method to parse variables
 *
 */
static void variable(bool canAssign) {
    namedVariable(parser.previous, canAssign);
}

/**
 * @brief Method to deal with the unary minus
 *
 */
static void unary(bool canAssign) {
    TokenType operatorType = parser.previous.type;

    // compiling the operand
    parsePrecedence(PREC_UNARY);

    // emit operator instruction
    switch (operatorType) {
        case TOKEN_BANG:  emitByte(OP_NOT); break;
        case TOKEN_MINUS: emitByte(OP_NEGATE); break;
        default: return; // unreachable
    }
}

/**
 * @brief The array of parse rules
 *
 */
ParseRule rules[] = {
    [TOKEN_LEFT_PAREN]    = {grouping, NULL,   PREC_NONE},
    [TOKEN_RIGHT_PAREN]   = {NULL,     NULL,   PREC_NONE},
    [TOKEN_LEFT_BRACE]    = {NULL,     NULL,   PREC_NONE}, 
    [TOKEN_RIGHT_BRACE]   = {NULL,     NULL,   PREC_NONE},
    [TOKEN_COMMA]         = {NULL,     NULL,   PREC_NONE},
    [TOKEN_DOT]           = {NULL,     NULL,   PREC_NONE},
    [TOKEN_MINUS]         = {unary,    binary, PREC_TERM},
    [TOKEN_PLUS]          = {NULL,     binary, PREC_TERM},
    [TOKEN_SEMICOLON]     = {NULL,     NULL,   PREC_NONE},
    [TOKEN_SLASH]         = {NULL,     binary, PREC_FACTOR},
    [TOKEN_STAR]          = {NULL,     binary, PREC_FACTOR},
    [TOKEN_MOD]           = {NULL,     binary, PREC_FACTOR},
    [TOKEN_BANG]          = {unary,    NULL,   PREC_NONE},
    [TOKEN_BANG_EQUAL]    = {NULL,     binary, PREC_EQUALITY},
    [TOKEN_EQUAL]         = {NULL,     NULL,   PREC_NONE},
    [TOKEN_EQUAL_EQUAL]   = {NULL,     binary, PREC_COMPARISON},
    [TOKEN_GREATER]       = {NULL,     binary, PREC_COMPARISON},
    [TOKEN_GREATER_EQUAL] = {NULL,     binary, PREC_COMPARISON},
    [TOKEN_LESS]          = {NULL,     binary, PREC_COMPARISON},
    [TOKEN_LESS_EQUAL]    = {NULL,     binary, PREC_COMPARISON},
    [TOKEN_IDENTIFIER]    = {variable, NULL,   PREC_NONE},
    [TOKEN_STRING]        = {string,   NULL,   PREC_NONE},
    [TOKEN_NUMBER]        = {number,   NULL,   PREC_NONE},
    [TOKEN_AND]           = {NULL,     NULL,   PREC_NONE},
    [TOKEN_CLASS]         = {NULL,     NULL,   PREC_NONE},
    [TOKEN_ELSE]          = {NULL,     NULL,   PREC_NONE},
    [TOKEN_FALSE]         = {literal,  NULL,   PREC_NONE},
    [TOKEN_FOR]           = {NULL,     NULL,   PREC_NONE},
    [TOKEN_FUN]           = {NULL,     NULL,   PREC_NONE},
    [TOKEN_IF]            = {NULL,     NULL,   PREC_NONE},
    [TOKEN_NULL]          = {literal,  NULL,   PREC_NONE},
    [TOKEN_OR]            = {NULL,     NULL,   PREC_NONE},
    [TOKEN_PRINT]         = {NULL,     NULL,   PREC_NONE},
    [TOKEN_RETURN]        = {NULL,     NULL,   PREC_NONE},
    [TOKEN_SUPER]         = {NULL,     NULL,   PREC_NONE},
    [TOKEN_THIS]          = {NULL,     NULL,   PREC_NONE},
    [TOKEN_TRUE]          = {literal,  NULL,   PREC_NONE},
    [TOKEN_VAR]           = {NULL,     NULL,   PREC_NONE},
    [TOKEN_WHILE]         = {NULL,     NULL,   PREC_NONE},
    [TOKEN_ERROR]         = {NULL,     NULL,   PREC_NONE},
    [TOKEN_EOF]           = {NULL,     NULL,   PREC_NONE},
};

/**
 * @brief Starts at current token, and parses any expression at the given
 * precedence level or higher.
 *
 */
static void parsePrecedence(Precedence precedence) {
    advance();
    ParseFn prefixRule = getRule(parser.previous.type)->prefix;

    if (prefixRule==NULL) {
        error("Expect expression.");
        return;
    }

    // checking if assignment can happen
    bool canAssign = precedence <= PREC_ASSIGNMENT;
    prefixRule(canAssign);

    while (precedence <= getRule(parser.current.type)->precedence) {
        advance();
        ParseFn infixRule = getRule(parser.previous.type)->infix;
        infixRule(canAssign);
    }

    if (canAssign && match(TOKEN_EQUAL)) {
        error("Invalid assignment target.");
    }
}


/**
 * @brief Method to write the constant name as a string to the table
 *
 * @param name Name of the token
 * @return uint8_t index of the constant in the program
 */
static uint8_t identifierConstant(Token* name) {
    return makeConstant(OBJ_VAL(copyString(name->start,
                    name->length)));
}

/**
 * @brief Method to parse a variable declaration and expect an identifier
 *
 * @param errorMessage Error message to emit when no identifier is found
 * @return uint8_t index of the constant in the constant array
 */
static uint8_t parseVariable(const char* errorMessage) {
    consume(TOKEN_IDENTIFIER, errorMessage);
    return identifierConstant(&parser.previous);
}

/**
 * @brief Method to output the bytecode instruction that defines the new
 * variable and stores its initial value
 *
 * @param global Variable index
 */
static void defineVariable(uint8_t global) {
    emitBytes(OP_DEFINE_GLOBAL, global);
}

/**
 * @brief A method that indexes the parsing rules table based on type. The
 * lookup is wrapped in a function.
 *
 */
static ParseRule* getRule(TokenType type) {
    return &rules[type];
}

/**
 * @brief Method to parse expressions
 *
 */
static void expression() {
    parsePrecedence(PREC_ASSIGNMENT);
}

/**
 * @brief Method to parse blocks inside braces. Expects a closing curly brace
 *
 */
static void block() {
    while (!check(TOKEN_RIGHT_BRACE) && !check(TOKEN_EOF)) {
        declaration();
    }

    consume(TOKEN_RIGHT_BRACE, "Expect '}' after block.");
}

/**
 * @brief A method to handle variable declarations.
 */
static void varDeclaration() {
    uint8_t global = parseVariable("Expect variable name.");

    if (match(TOKEN_EQUAL)) {
        expression();
    } else {
        emitByte(OP_NULL);
    }
    consume(TOKEN_SEMICOLON, "Expect ';' after variable declaration");

    defineVariable(global);
}

/**
 * @brief Method to compile an expression followed by a semicolon.
 *
 */
static void expressionStatement() {
    expression();
    consume(TOKEN_SEMICOLON, "Expect ';' after expression.");
    emitByte(OP_POP);
}

/**
 * @brief Method to handle print statements
 */
static void printStatement() {
    expression();
    consume(TOKEN_SEMICOLON, "Expect ';' after value.");
    emitByte(OP_PRINT);
}

/**
 * @brief Method to synchronize panic mode. Allows the compiler to exit
 * panic mode when it reaches a synchronization point.
 */
static void synchronize() {
    parser.panicMode = false;

    while (parser.current.type != TOKEN_EOF) {
        if (parser.previous.type == TOKEN_SEMICOLON) return;
        switch (parser.current.type) {
            case TOKEN_CLASS:
            case TOKEN_FUN:
            case TOKEN_VAR:
            case TOKEN_FOR:
            case TOKEN_IF:
            case TOKEN_WHILE:
            case TOKEN_PRINT:
            case TOKEN_RETURN:
                return;

            default:
                ; // do nothing
        }
        advance();
    }
}

/**
 * @brief Method to compile a single declaration
 *
 */
static void declaration() {
    if (match(TOKEN_VAR)) {
        varDeclaration();
    } else {
        statement();
    }

    // if parser gets into panic mode, we synchronize
    if (parser.panicMode) synchronize();
}

/**
 * @brief Method to match statements according to their tokens
 * 
 */
static void statement() {
    if (match(TOKEN_PRINT)) {
        printStatement();
    } else if (match(TOKEN_LEFT_BRACE)) {
        beginScope();
        block();
        endScope();
    } else {
        expressionStatement();
    }
}

bool compile(const char *source, Chunk* chunk) {
    initScanner(source);
    Compiler compiler;
    initCompiler(&compiler);
    compilingChunk = chunk;

    // initializing error state
    parser.hadError = false;
    parser.panicMode = false;

    advance();
    while (!match(TOKEN_EOF)) {
        declaration();
    }
    endCompiler();
    return !parser.hadError;
}
