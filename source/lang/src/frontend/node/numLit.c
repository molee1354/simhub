#include <stdlib.h>

#include "node.h"

NumLit* newNumLit( double value ) {
    NumLit* out = (NumLit*)malloc(sizeof(NumLit));
    out->exprKind = newExpression(NumericLiteral_Node);
    out->value = value;
    return out;
}

void freeNumLit( NumLit* numLit ) {
    freeExpression(numLit->exprKind);
    numLit->exprKind = NULL;
    free(numLit);
    numLit = NULL;
}
