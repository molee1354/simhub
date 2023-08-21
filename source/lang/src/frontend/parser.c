#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "node/node.h"
#include "token/token.h"

/**
 * All the parsing is done on the token array, so every parsing function
 * must have a token array argument passed in.
 */

#define ERR_EXIT(reason)    fprintf(stderr, "Parse Error:\n%s\n", reason); \
                            exit(1);

int notEof(Token* currentToken) {
    return currentToken->type == EndOfFile;
}

Token currentToken(Array* tokenArray) {
    Token out = getElement(tokenArray, 0);
    return out;
}

Token advanceToken(Array* tokenArray) {
    Token out = getElement(tokenArray, 0);
    deleteHead(tokenArray);
    return out;
}

Token expectToken(Array* tokenArray, TokenType expected) {
    Token curTok = advanceToken(tokenArray);
    if ( curTok.type!=expected ) {
        fprintf(stderr,
                "Parse Error:\nExpected : %d\n\tReceived : %d\n",
                curTok.type, expected);
        exit(1);
    }
    return curTok;
}

void parseStatement(Array* tokenArray, void** outStmt) {
    parseExpression(tokenArray, outStmt);
}

void parseExpression(Array* tokenArray, void** outExpr) {
    parseAddExpression(tokenArray, outExpr);
}

void parseAddExpression(Array* tokenArray, void** outExpr) {
    void* left = NULL;
    parseMultExpression(tokenArray, &left);
    Token curTok = currentToken(tokenArray);

    // if the current token is a additive operator
    while ( !strcmp("+",curTok.value) ||
            !strcmp("-",curTok.value) )
    {
        // create a new binary expression
        void* right = NULL;
        parseMultExpression(tokenArray, &right);
        *outExpr = newBinExpr(left, right, curTok.value);
        return;
    }
    *outExpr = left;
}

void parseMultExpression(Array* tokenArray, void** outExpr) {
    void* left = NULL;
    parsePrimaryExpression(tokenArray, &left);
    Token curTok = currentToken(tokenArray);

    // if the current token is a multiplicative operator
    while ( !strcmp("*",curTok.value) ||
            !strcmp("/",curTok.value) ||
            !strcmp("%",curTok.value) )
    {
        // create a new binary expression
        void* right = NULL;
        parsePrimaryExpression(tokenArray, &right);
        *outExpr = newBinExpr(left, right, curTok.value);
        return;
    }
    *outExpr = left;
}

/**
 * When calling the function, call a null pointer and use an ampersand (&)
 *
 */
void parsePrimaryExpression(Array* tokenArray, void** outExpr) {
    Token curTok = currentToken(tokenArray);

    if      (curTok.type == Identifier) {
        Token outToken = advanceToken(tokenArray);
        *outExpr = newIdent(outToken.value);
    }
    else if (curTok.type == Number) {
        Token outToken = advanceToken(tokenArray);
        double dvalue;
        if ( !sscanf(outToken.value, "%lf", &dvalue) ) {
            ERR_EXIT("\tNumeric literal has unrecognizable format");
        }
        *outExpr = newNumLit(dvalue);
    }
    else if (curTok.type == OpenParen) {
        Token _prev = advanceToken(tokenArray);
        void* value = NULL;
        parseExpression(tokenArray, value);
        _prev = expectToken(tokenArray, CloseParen);
        *outExpr = value;
    }
    else {
        ERR_EXIT("\tUnexpected token found during parsing\n");
    }
}
