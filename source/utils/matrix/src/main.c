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

    double targ = 1.;
    modMatrix[2][2] = targ;

    puts("\nprintMatrix()");
    printMatrix(myMatrix);

    int* matIdx = getIndex(myMatrix, targ);
    printf("\ngetIdx_v for targ %.2f = [%d, %d]\n", targ,
            matIdx[0], matIdx[1]);
    free(matIdx);

    puts("\ngetSize()");
    int* size = getSize(myMatrix);
    printf("size : [");
    printf("%d, ", size[0]);
    printf("%d]\n", size[1]);

    /*double* nVector = (double*)malloc(sizeof(double)*NCOL);
    for (int i=0; i<NCOL; i++) nVector[i] = i+1; */

    // Vector* myVector = toVector(nVector, NCOL, ROW);
    Vector* myVector = zeros(NCOL, ROW);
    puts("\nprintVector()");
    double* modVector = makeModifiable(myVector);
    modVector[1] = targ;
    printVector(myVector);

    int vecIdx = getIndex(myVector, targ);
    printf("\ngetIdx_v for targ %.2f = %d\n", targ, vecIdx);

    puts("\nmatRepr()");
    matRepr(myMatrix);

    puts("\nfreeVector()");
    freeVector(myVector);

    puts("\nfreeMatrix()");
    freeMatrix(myMatrix);

    puts("\nfreeModifiable()\n");

    return 0;
}
