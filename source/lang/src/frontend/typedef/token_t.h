#ifndef _token_t_h
#define _token_t_h

/**
 * @brief Enum to hold the different types of tokens
 *
 */
#include "array_t.h"
typedef enum {
    Number,
    Identifier,
    Equals,
    OpenParen,
    CloseParen,
    BinaryOperator,

    Let,

    End, // handles the ends of the token linked list
    EndOfLine,
    EndOfFile
} TokenType;

/**
 * @brief Token struct
 *
 */
typedef struct UserToken {
    TokenType type;
    char* value;
} Token;

/**
 * @brief TokenNode struct definition
 *
 * This is a single node for the linked list, and really has nothing to do with
 * the 'Node' in 'NodeType' for AST nodes
 *
 */
typedef struct Array_TokenNode { 
    Token token;
    struct Array_TokenNode* next;
} Node;

#endif
