#include <stdio.h>
#include <stdlib.h>

#include "node.h"

Program* newProgram( Statement** prgmBody ) {
    Program* out = (Program*)malloc(sizeof(Program));
    if (out==NULL) {
        fprintf(stderr, "Could not allocate memory for new Program");
        return NULL;
    }
    out->stmtKind = newStatement(Program_Node);
    out->body = prgmBody;
    return out;
}

void freeProgram( Program* prgm, int stmtLength ) {
    for (int i=0; i<stmtLength; i++) {
        freeStatement(prgm->body[i]);
        // no null statement as the function above already implements null
    }
    freeStatement(prgm->stmtKind);
    prgm->stmtKind = NULL;
    free(prgm->body);
    prgm->body = NULL;
    free(prgm);
    prgm = NULL;
}
