#ifndef _parser_h
#define _parser_h

#include "frontend.h"

/**
 * @brief Method to produce an AST given a sourcecode
 *
 * @param sourceCode
 * @return Prgm*
 */
Prgm* produceAST(char* sourceCode);

/**
 * @brief Method to check if the current token is an EOF token
 * 
 * @param currentToken the current token
 * @return int
 */
int notEof(Token* currentToken);

/**
 * @brief Method to return the current token
 *
 * @param tokenArray array of tokens
 * @return Token
 */
Token currentToken(Array* tokenArray);

/**
 * @brief Method to return the previous token and advance current token
 * to the next token
 *
 * @param tokenArray array of tokens
 * @return Token
 */
Token advanceToken(Array* tokenArray);

/**
 * @brief Method to return the previous token and advance current token
 * to the next token. Also checks if the token is of expected type
 *
 * @param tokenArray array of tokens
 * @param expected expected token
 * @return Token
 */
Token advanceCheckToken(Array* tokenArray, TokenType expected);

/**
 * @brief Method to parse statements
 *
 * @param tokenArray
 * @return Stmt*
 */
Stmt* parseStmt(Array* tokenArray);

/**
 * @brief Method to parse expressions
 *
 * @param tokenArray
 * @return Stmt*
 */
Expr* parseExpr(Array* tokenArray);

/**
 * @brief Method to parse additive expressions
 *
 * @param tokenArray
 * @return Stmt*
 */
Expr* parseAddExpr(Array* tokenArray);

/**
 * @brief Method to parse multiplicative expressions
 *
 * @param tokenArray
 * @return Stmt*
 */
Expr* parseMultExpr(Array* tokenArray);

/**
 * @brief Method to parse primary expressions
 *
 * @param tokenArray
 * @return Stmt*
 */
Expr* parsePrimaryExpr(Array* tokenArray);


#endif
