#include <stdlib.h>

#include "node.h"

BinExpr* newBinExpr(
        Expression* left,
        Expression* right, char* string ) {
    BinExpr* out = (BinExpr*)malloc(sizeof(BinExpr));

    out->exprKind = newExpression(BinaryExpression_Node);
    out->left = left;
    out->right = right;
    out->string = string;

    return out;
}

void freeBinExpr(BinExpr* binExpr) {
    freeExpression(binExpr->exprKind);
    freeExpression(binExpr->left);
    freeExpression(binExpr->right);
    free(binExpr->string);
}
