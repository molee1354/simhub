#include<stdio.h>
#include<stdlib.h>

#include "matrix.h"

#define NROW 3
#define NCOL 3

int main() {
    // double** nMatrix = (double**)malloc(sizeof(double*)*NROW);
    // for (int i=0; i<NROW; i++) {
    //     nMatrix[i] = (double*)malloc(sizeof(double)*NCOL);
    // }
    // int n = 1;
    // for (int i=0; i<NROW; i++) {
    //     for (int j=0; j<NCOL; j++) {
    //         nMatrix[i][j] = n++;
    //     }
    // }

    // Matrix* myMatrix = toMatrix(nMatrix, NROW, NCOL);
    // Matrix* myMatrix = ones(NROW, NCOL);
    Matrix* myMatrix = eye(NCOL);
    double** modMatrix = makeModifiable(myMatrix);
    modMatrix[1][1] = -1.;

    puts("\nprintMatrix()");
    printMatrix(myMatrix);

    /*double* nVector = (double*)malloc(sizeof(double)*NCOL);
    for (int i=0; i<NCOL; i++) nVector[i] = i+1; */

    // Vector* myVector = toVector(nVector, NCOL, ROW);
    Vector* myVector = zeros(NCOL, ROW);
    puts("\nprintVector()");
    printVector(myVector);

    puts("\nmatRepr()");
    matRepr(myMatrix);

    puts("\nfreeVector()");
    freeVector(myVector);

    puts("\nfreeMatrix()");
    freeMatrix(myMatrix);

    puts("\nfreeModifiable()");
    freeModifiable(modMatrix, NCOL);

    return 0;
}
