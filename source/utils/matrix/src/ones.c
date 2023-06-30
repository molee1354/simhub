#include <stdlib.h>
#include "matrix.h"
#include "_matrix.h"


Matrix* ones_M( int numRows, int numCols ) {
    Matrix* out = (Matrix*)malloc(sizeof(Matrix));
    if (out==NULL) return out;

    // zero matrix of given size
    out->e = (double**)calloc(numRows, sizeof(double*));
    for (int i=0; i<numRows; i++) {
        out->e[i] = (double*)calloc(numCols, sizeof(double));
    }

    // setting all the values to one
    for (int i=0; i<numRows; i++) {
        for (int j=0; j<numCols; j++) {out->e[i][j] = 1;}
    }

    out->nRows = numRows; out->size[0] = numRows;
    out->nCols = numCols; out->size[1] = numCols;
    out->isSquare = (numRows == numCols) ? 1 : 0;
    
    return out;
}
Vector* ones_V( int numElem, vType direction ) {
    Vector* out = (Vector*)malloc(sizeof(Vector));
    out->e = (double*)calloc(numElem, sizeof(double));
    for (int i=0; i<numElem; i++) {out->e[i] = 1;}
    out->nEle = numElem;
    out->direction = direction;
    return out;
}
