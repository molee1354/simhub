#include <stdio.h>
#include <stdlib.h>

#include "node.h"

Prgm* newProgram( NodeType kind, Statement** prgmBody ) {
    Prgm* out = (Prgm*)malloc(sizeof(Prgm));
    if (out==NULL) {
        fprintf(stderr, "Could not allocate memory for new Program");
        return NULL;
    }
    out->stmtKind->kind = kind;
    out->body = prgmBody;
    return out;
}

void freeProgram( Prgm* prgm, int stmtLength ) {
    for (int i=0; i<stmtLength; i++) {
        freeStatement(prgm->body[i]);
        // no null statement as the function above already implements null
    }
    free(prgm->body);
    prgm->body = NULL;
    free(prgm);
    prgm = NULL;
}
