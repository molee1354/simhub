#ifndef _parser_h
#define _parser_h

#include "node/node.h"

/**
 * @brief Method to produce an AST given a sourcecode
 *
 * @param sourceCode
 * @return Prgm*
 */
Program* produceAST(char* sourceCode);

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
Token expectToken(Array* tokenArray, TokenType expected);

/**
 * @brief Method to parse statements
 *
 * @param tokenArray
 * @return Statement*
 */
Statement* parseStatement(Array* tokenArray);

/**
 * @brief Method to parse expressions
 *
 * @param tokenArray
 * @return Expression*
 */
Expression* parseExpression(Array* tokenArray);

/**
 * @brief Method to parse additive expressions
 *
 * @param tokenArray
 * @return Expression*
 */
Expression* parseAddExpression(Array* tokenArray);

/**
 * @brief Method to parse multiplicative expressions
 *
 * @param tokenArray
 * @return Expression*
 */
Expression* parseMultExpression(Array* tokenArray);

/**
 * @brief Method to parse primary expressions
 *
 * @param tokenArray
 * @param outExpr a double void pointer that holds the pointer to the parsed 
 * expression
 *
 */
void parsePrimaryExpression(Array* tokenArray, void** outExpr);


#endif
