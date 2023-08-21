#ifndef _token_h
#define _token_h

/*
 * Enum to hold the different types of tokens
 */
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

/*
 * Token struct
 */
typedef struct UserToken {
    TokenType type;
    char* value;
} Token;

#endif
