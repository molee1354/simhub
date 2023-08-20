#ifndef _lang_h_
#define _lang_h_

#include "../deps/token.h"
#include "../deps/array.h"

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
    Program,
    NumericLiteral,
    IdentifierNode,
    IdentifierBinaryExpr,
} NodeType;

/**
 * @brief Base statement "interface" for implementation. Does not result
 * in a value at runtime
 * 
 */
typedef struct Statement {
    NodeType kind;
} Stmt;

/**
 * @brief Constructor for base statement class
 * 
 * @param kind NodeType of statement
 * @return Stmt* 
 */
Stmt* newStatement( NodeType kind );

/**
 * @brief Base expression interface for implementation. Does result in a
 * value at runtime
 * 
 */
typedef struct Expression {
    Stmt* exprKind;
} Expr;

/**
 * @brief Constructor for base expression struct. Sets NodeType for expression
 * 
 * @param kind NodeType of expression
 * @return Expr* 
 */
Expr* newExpression( NodeType kind );

/**
 * @brief Program handle. Implements statement with field once initialized.
 * 
 */
typedef struct ProgramNode {
    Stmt* stmtKind;
    Stmt** body;
} Prgm;

/**
 * @brief Constructor for program struct. Sets nodetype for program
 *
 * @param kind NodeType of program
 * @param prgmBody Body of program as an array of statements
 * @return Prgm*
 */
Prgm* newProgram( NodeType kind, Stmt** prgmBody );

/**
 * @brief Binary expression implementation
 * 
 */
typedef struct BinaryExprNode {
    Expr* exprKind;
    Expr* left;
    Expr* right;
    char* string; // needs to be of type BinaryOperator
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
BinExpr* newBinExpr( NodeType kind, Expr* left, Expr* right, char* string );

/**
 * @brief Identifier implementation
 * 
 */
typedef struct IdentifierNode {
    Expr* exprKind;
    char* string;
} Ident;


/**
 * @brief Constructor for identifier struct. Sets nodetype for Ident
 *
 * @param kind NodeType of Ident
 * @param string string value for Ident
 * @return Ident*
 */
Ident* newIdent( NodeType kind, char* string );

/**
 * @brief NumericLiteralNode implementation
 * 
 */
typedef struct NumericLiteralNode {
    Expr* exprKind;
    double value;
} NumLit;

/**
 * @brief Constructor for numeric literal. Sets nodetype for NumLit
 *
 * @param kind NodeType for NumLit
 * @param value double value for NumLit
 * @return NumLit*
 */
NumLit* newNumLit( NodeType kind, double value );

#endif
