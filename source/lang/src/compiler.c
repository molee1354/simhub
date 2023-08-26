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
typedef void (*ParseFn)();

/**
 * @brief Wrapper for a single row in the parser table
 *
 */
typedef struct {
    ParseFn prefix;
    ParseFn infix;
    Precedence precedence;
} ParseRule;

Parser parser;
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

/* Wrapper function declarations */
static void expression();
static void statement();
static void declaration();
static ParseRule* getRule(TokenType type);
static void parsePrecedence(Precedence precedence);

/**
 * @brief Method to handle binary operations
 *
 */
static void binary() {
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
static void literal() {
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
static void grouping() {
    expression(); // takes care of generating bytecode inside the parenthesis
    consume(TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
}

/**
 * @brief Method to convert a parsed string to a number
 *
 */
static void number() {
    double value = strtod(parser.previous.start, NULL);
    emitConstant(NUMBER_VAL(value));
}

/**
 * @brief Method to convert a parsed string into string value
 */
static void string() {
    emitConstant( OBJ_VAL(copyString(parser.previous.start + 1,
                                     parser.previous.length -2)) );
}

/**
 * @brief Method to deal with the unary minus
 *
 */
static void unary() {
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
    [TOKEN_IDENTIFIER]    = {NULL,     NULL,   PREC_NONE},
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

    prefixRule();

    while (precedence <= getRule(parser.current.type)->precedence) {
        advance();
        ParseFn infixRule = getRule(parser.previous.type)->infix;
        infixRule();
    }
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
 * @brief Method to handle print statements
 */
static void printStatement() {
    expression();
    consume(TOKEN_SEMICOLON, "Expect ';' after value.");
    emitByte(OP_PRINT);
}

/**
 * @brief Method to compile a single declaration
 *
 */
static void declaration() {
    statement();
}

/**
 * @brief Method to match statements according to their tokens
 * 
 */
static void statement() {
    if (match(TOKEN_PRINT)) {
        printStatement();
    }
}

bool compile(const char *source, Chunk* chunk) {
    initScanner(source);
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
