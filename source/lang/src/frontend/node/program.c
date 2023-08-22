#include <stdio.h>
#include <stdlib.h>

#include "node.h"

Program* newProgram( Array* prgmBody ) {
    Program* out = (Program*)malloc(sizeof(Program));
    if (out==NULL) {
        fprintf(stderr, "Could not allocate memory for new Program");
        return NULL;
    }
    out->stmtKind = newStatement(Program_Node);
    out->body = prgmBody;
    return out;
}

void freeProgram( Program* prgm ) {
    freeStatement(prgm->stmtKind);
    freeArray(prgm->body);
    // no null statement as the function above already implements null

    free(prgm);
    prgm = NULL;
}
