#include <stdlib.h>

#include "node.h"

BinExpr* newBinExpr(
        Expression* left,
        Expression* right, char* operation ) {
    BinExpr* out = (BinExpr*)malloc(sizeof(BinExpr));

    out->exprKind = newExpression(BinaryExpression_Node);
    out->left = left;
    out->right = right;
    out->operation = operation;

    return out;
}

void freeBinExpr(BinExpr* binExpr) {
    freeExpression(binExpr->exprKind);
    binExpr->exprKind = NULL;
    freeExpression(binExpr->left);
    binExpr->left = NULL;
    freeExpression(binExpr->right);
    binExpr->right = NULL;
}
