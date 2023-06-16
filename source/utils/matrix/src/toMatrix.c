#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "guard.h"

Matrix* toMatrix( double** nMatrix, int numRows, int numCols ) {
    Matrix* out = (Matrix*)malloc(sizeof(Matrix));
    if (out==NULL) return out;

    out->e = nMatrix;
    out->nRows = numRows;
    out->nCols = numCols;
    out->size[0] = numRows;
    out->size[1] = numCols;
    out->isSquare = (numRows == numCols) ? 1 : 0;
    
    /* double Vector pointer to hold Vector* objects that represent
       each row and column in the matrix */
    int rcCount = numRows+numCols;
    out->rowsNcols = (Vector**)malloc(sizeof(Vector*)*(rcCount));
    /* for (int i=0; i<rcCount; i++) {
        if (i<numRows) {
            Vector* rowVect = toVector( nMatrix[i], numCols, ROW);
            out->rowsNcols[i] = rowVect;
        } else {
            Vector* colVect = makeVector(numRows, COL);
            for (int j=0; j<numCols; j++) {
                for (int k=0; k<numRows; k++) {
                    colVect->e[k] = nMatrix[k][j];
                    printf("nMat[%d][%d] : %7.2f\n", k,j,nMatrix[k][j]);
                } 
                out->rowsNcols[i] = colVect; 
                printf("set rowsNcols[%d] to: ", i);
                printVector(colVect);
                puts("");
                i++;
            } 
        } 
    } */
    int i = 0;
    for (; i<numRows; i++) {
        Vector* rowVect = toVector( nMatrix[i], numCols, ROW);
        out->rowsNcols[i] = rowVect;
    }
    for (; i<rcCount; i++) {
        Vector* colVect = makeVector(numRows, COL);
        for (int j=0; j<numCols; j++) {
            for (int k=0; k<numRows; k++) {
                colVect->e[k] = nMatrix[k][j];
                printf("nMat[%d][%d] : %7.2f\n", k,j,nMatrix[k][j]);
            } 
            out->rowsNcols[i] = colVect; 
            printf("set rowsNcols[%d] to: ", i);
            printVector(colVect);
            puts("");
        } 
    }
    return out;
}
