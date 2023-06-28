#include <stdlib.h>
#include "matrix.h"
#include "guard.h"


Matrix* makeMatrix( int numRows, int numCols ) {
    Matrix* out = (Matrix*)malloc(sizeof(Matrix));
    if (out==NULL) return out;

    // zero matrix of given size
    out->e = (double**)calloc(numRows, sizeof(double*));
    for (int i=0; i<numRows; i++) {
        out->e[i] = (double*)calloc(numCols, sizeof(double));
    }
    out->nRows = numRows; out->size[0] = numRows;
    out->nCols = numCols; out->size[1] = numCols;
    out->isSquare = (numRows == numCols) ? 1 : 0;
    
    return out;
}
