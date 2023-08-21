#ifndef _node_h_
#define _node_h_

/* #include "../../deps/token.h"
#include "../../deps/array.h" */

#include "../token/array.h"
#include "../token/token.h"

/* Lexer Defs */

/**
 * @brief Function to match a token to a word
 * 
 * @param word word for token type
 * @param t_type token type to match
 * @return Token* 
 */
Token* token(char* word, TokenType t_type);

/**
 * @brief Function to tokenize the source code into an array of tokens
 * 
 * @param sourceCode character array of source code 
 * @param srcSize the size of the character array
 * @return Array* 
 */
Array* tokenize(char* sourceCode, int srcSize);


/* AST Defs */

/**
 * @brief Holding the different types of nodes
 * 
 */
typedef enum {
    Program_Node,
    NumericLiteral_Node,
    Identifier_Node,
    BinaryExpression_Node,
} NodeType;

/**
 * @brief Base statement "interface" for implementation. Does not result
 * in a value at runtime
 * 
 */
typedef struct StatementNode {
    NodeType kind;
} Statement;

/**
 * @brief Constructor for base statement class
 * 
 * @param kind NodeType of statement
 * @return Statement* 
 */
Statement* newStatement( NodeType kind );

/**
 * @brief Method to free the statement struct
 *
 * @param 
 *
 */
void freeStatement( Statement* stmt );

/**
 * @brief Base expression interface for implementation. Does result in a
 * value at runtime
 * 
 */
typedef struct ExpressionBaseNode {
    Statement* exprKind;
} Expression;

/**
 * @brief Constructor for base expression struct. Sets NodeType for expression
 * 
 * @param kind NodeType of expression
 * @return Expr* 
 */
Expression* newExpression( NodeType kind );

/**
 * @brief Method to free the expression struct
 *
 * @param 
 *
 */
void freeExpression( Expression* binExpr );

/**
 * @brief Program handle. Implements statement with field once initialized.
 * 
 */
typedef struct ProgramNode {
    Statement* stmtKind;
    Statement** body;
} Program;

/**
 * @brief Constructor for program struct. Sets nodetype for program
 *
 * @param kind NodeType of program
 * @param prgmBody Body of program as an array of statements
 * @return Program*
 */
Program* newProgram( Statement** prgmBody );

/**
 * @brief Method to free the memory allocated for a program node
 *
 * @param prgm Pointer to a program node to free
 * @param stmtLength length of program statement
 */
void freeProgram( Program* prgm, int stmtLength );

/**
 * @brief Binary expression implementation
 * 
 */
typedef struct BinaryExprNode {
    Expression* exprKind;
    Expression* left;
    Expression* right;
    char* operation; // needs to be of type BinaryOperator
} BinExpr;

/**
 * @brief Constructor for binary expression struct. Sets nodetype for BinExpr
 *
 * @param kind NodeType of BinExpr
 * @param left
 * @param left
 * @param string String value of BinExpr
 * @return BinExpr*
 */
BinExpr* newBinExpr( Expression* left, Expression* right, char* operation );

/**
 * @brief Method to free a binary expression struct
 *
 * @param binExpr pointer to a binary expression node to free
 *
 */
void freeBinExpr( BinExpr* binExpr );

/**
 * @brief Identifier implementation
 * 
 */
typedef struct IdentifierNode {
    Expression* exprKind;
    char* string;
} Ident;


/**
 * @brief Constructor for identifier struct. Sets nodetype for Ident
 *
 * @param kind NodeType of Ident
 * @param string string value for Ident
 * @return Ident*
 */
Ident* newIdent( char* string );

/**
 * @brief Method to free a identifier node struct
 *
 * @param identifier pointer to a identifier node to free
 *
 */
void freeIdent( Ident* ident );

/**
 * @brief NumericLiteralNode implementation
 * 
 */
typedef struct NumericLiteralNode {
    Expression* exprKind;
    double value;
} NumLit;

/**
 * @brief Constructor for numeric literal. Sets nodetype for NumLit
 *
 * @param kind NodeType for NumLit
 * @param value double value for NumLit
 * @return NumLit*
 */
NumLit* newNumLit( double value );

/**
 * @brief Method to free a numeric literal node struct
 *
 * @param identifier pointer to a numeric literal node to free
 *
 */
void freeNumLit( NumLit* numLit );

#endif