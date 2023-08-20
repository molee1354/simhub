#include <stdio.h>

#include "node.h"

BinExpr* newBinExpr(
        NodeType kind,
        Expression* left,
        Expression* right, char* string ) {
    BinExpr* out = (BinExpr*)malloc(sizeof(BinExpr));

    out->exprKind->exprKind = kind;
    out->left = left;
    out->right = right;
    out->string = string;

    return out;
}

void freeBinExpr(BinExpr* binExpr) {
    freeExpression(binExpr->exprKind);
    freeExpression(binExpr->left);
    freeExpression(binExpr->right);
    free(string);
}
