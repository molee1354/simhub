#include <stdlib.h>
#include "matrix.h"
#include "guard.h"

Matrix* eye( int sideLength ) {
    Matrix* out = (Matrix*)malloc(sizeof(Matrix));
    if (out==NULL) return out;

    // zero matrix of given size
    out->e = (double**)calloc(sideLength, sizeof(double*));
    for (int i=0; i<sideLength; i++) {
        out->e[i] = (double*)calloc(sideLength, sizeof(double));
    }
    for (int i=0; i<sideLength; i++) {
        for (int j=0; j<sideLength; j++) {if (i==j) {out->e[i][j] = 1;}}
    }
    out->nRows = sideLength; out->size[0] = sideLength;
    out->nCols = sideLength; out->size[1] = sideLength;
    out->isSquare = 1;
    
    /* double Vector pointer to hold Vector* objects that represent
       each row and column in the matrix */
    int rcCount = sideLength+sideLength;
    out->rowsNcols = (Vector**)malloc(sizeof(Vector*)*rcCount);
    int i = 0;
    for (; i<sideLength; i++) {
        Vector* rowVect = toVector( out->e[i], sideLength, ROW);
        out->rowsNcols[i] = rowVect;
    }
    for (; i<rcCount; i++) {
        int j = i-sideLength;
        Vector* colVect = makeVector(sideLength, COL);
        for (int k=0; k<sideLength; k++) {
            colVect->e[k] = out->e[k][j];
        }
        out->rowsNcols[i] = colVect;
    }
    return out;

}
