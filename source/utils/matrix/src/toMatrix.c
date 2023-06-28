#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "guard.h"

Matrix* toMatrix( double** nMatrix, int numRows, int numCols ) {
    Matrix* out = (Matrix*)malloc(sizeof(Matrix));
    if (out==NULL) return out;

    out->e = nMatrix;
    out->nRows = numRows; out->size[0] = numRows;
    out->nCols = numCols; out->size[1] = numCols;
    out->isSquare = (numRows == numCols) ? 1 : 0;
    
    return out;
}
