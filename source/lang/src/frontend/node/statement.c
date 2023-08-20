#include <stdlib.h>
#include <stdio.h>

#include "node.h"

Statement* newStatement( NodeType kind ) {
    Statement* out = (Statement*)malloc(sizeof(Statement));
    if (out==NULL) {
        fprintf(stderr, "Could not allocate memory for new Statement");
        return NULL;
    }
    out->kind = kind;
    return out;
}

void freeStatement( Statement *stmt ) {
    free(stmt);
    stmt = NULL;
}
