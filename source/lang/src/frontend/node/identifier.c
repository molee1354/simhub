#include <stdio.h>
#include <stdlib.h>

#include "node.h"

Ident* newIdent( char* string ) {
    Ident* out = (Ident*)malloc(sizeof(Ident));
    out->exprKind = newExpression(Identifier_Node);
    out->string = string;
    return out;
}

void freeIdent( Ident* ident ) {
    freeExpression(ident->exprKind);
    ident->exprKind = NULL;
    free(ident);
    ident = NULL;
}
