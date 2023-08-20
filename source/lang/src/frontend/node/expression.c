#include <stdlib.h>
#include <stdio.h>

#include "node.h"

Expression* newExpression( NodeType kind ) {
    Expression* out = (Expression*)malloc(sizeof(Expression));
    if (out==NULL) {
        fprintf(stderr, "Could not allocate memory for new Expression");
        return NULL;
    }
    out->exprKind = newStatement(kind);
    return out;
}

void freeExpression( Expression* binExpr ) {
    freeStatement(binExpr->exprKind);
    binExpr->exprKind = NULL;
    free(binExpr);
    binExpr = NULL;
}
