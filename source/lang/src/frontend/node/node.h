#ifndef _node_h_
#define _node_h_

#include "../utils/array.h"
#include "../types.h"

/**
 * Header file to define all the methods for the node types. The struct
 * definitions of the nodes all included in the 'types.h' header file.
 *
 */

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
 * @brief Constructor for program struct. Sets nodetype for program
 *
 * @param kind NodeType of program
 * @param prgmBody Body of program as an array of statements
 * @return Program*
 */
Program* newProgram( Array* prgmBody );

/**
 * @brief Method to free the memory allocated for a program node
 *
 * @param prgm Pointer to a program node to free
 * @param stmtLength length of program statement
 */
void freeProgram( Program* prgm );

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
