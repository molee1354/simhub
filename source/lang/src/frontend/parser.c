#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "frontend.h"
#include "parser.h"

/**
 * Defining statements, programs, and expressions
 */

Stmt* newStatement( NodeType kind ) {
    Stmt* out = (Stmt*)malloc(sizeof(Stmt));
    out->kind = kind;
    return out;
}

Expr* newExpression( NodeType kind ) {
    Expr* out = (Expr*)malloc(sizeof(Expr));
    Stmt* parentDef = newStatement(kind);

    out->exprKind = parentDef;
    return out;
}

Prgm* newProgram( NodeType kind, Stmt** prgmBody ) {
    Prgm* out = (Prgm*)malloc(sizeof(Prgm));
    Stmt* parentDef = newStatement(kind);

    out->stmtKind = parentDef;
    out->body = prgmBody;

    return out;
}
