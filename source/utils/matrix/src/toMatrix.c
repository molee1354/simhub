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
    
    /* double Vector pointer to hold Vector* objects that represent
       each row and column in the matrix */
    int rcCount = numRows+numCols;
    out->rowsNcols = (Vector**)malloc(sizeof(Vector*)*rcCount);
    int i = 0;
    for (; i<numRows; i++) {
        Vector* rowVect = toVector( out->e[i], numCols, ROW);
        out->rowsNcols[i] = rowVect;
    }
    for (; i<rcCount; i++) {
        int j = i-numRows;
        Vector* colVect = makeVector(numRows, COL);
        for (int k=0; k<numRows; k++) {
            colVect->e[k] = out->e[k][j];
        }
        out->rowsNcols[i] = colVect;
    }
    return out;
}
