#include <stdio.h>
#include <stdlib.h>

#include "node/node.h"
#include "parser.h"
#include "token/token.h"

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

Statement* parseStatement(Array* tokenArray) {}

Expression* parseExpression(Array* tokenArray) {}

Expression* parseAddExpression(Array* tokenArray) {}

Expression* parseMultExpression(Array* tokenArray) {}

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
        Expression* value = parseExpression(tokenArray);
        _prev = expectToken(tokenArray, CloseParen);
        *outExpr = value;
    }
    else {
        ERR_EXIT("\tUnexpected token found during parsing\n");
    }
}
