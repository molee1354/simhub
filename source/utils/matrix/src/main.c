#include<stdio.h>
#include<stdlib.h>

#include "matrix.h"

#define NROW 3
#define NCOL 3

int main() {
    double** nMatrix = (double**)malloc(sizeof(double*)*NROW);
    for (int i=0; i<NROW; i++) {
        nMatrix[i] = (double*)malloc(sizeof(double)*NCOL);
    }
    int n = 1;
    for (int i=0; i<NROW; i++) {
        for (int j=0; j<NCOL; j++) {
            nMatrix[i][j] = n++;
        }
    }

    // Matrix* myMatrix = toMatrix(nMatrix, NROW, NCOL);
    // Matrix* myMatrix = ones(NROW, NCOL);

    Matrix* myMatrix = ones(NROW, NCOL);
    Matrix* hisMatrix = toMatrix(nMatrix, NROW, NCOL);
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

    Matrix* matMultC = mult(myMatrix, 13.);
    Matrix* matMinus = minus(myMatrix, hisMatrix);
    Matrix* matMultE = mult_E(myMatrix, matMinus);
    Matrix* matSum = plus(myMatrix, hisMatrix);
    Matrix* matMultMM = mult(hisMatrix, matMultC);

    puts("\nmatrix const mult");
    printMatrix(matMultC);
    puts("\nmatrix element-wise mult");
    printMatrix(matMultE);

    puts("\nmatrix mult MM");
    printMatrix(hisMatrix);
    printMatrix(matMultC);
    printMatrix(matMultMM);

    puts("\nmatrix sum");
    printMatrix(matSum);
    puts("\nmatrix minus");
    printMatrix(matMinus);

    // matrix mult
    puts("\nmatrix mult Vec");
    Vector* vec2 = ones(3, COL);
    Matrix* mat2 = ones(3, 3);
    Matrix* mat3 = mult(mat2, 3.);
    Vector* matMultMV = mult(mat2, vec2);
    printVector(matMultMV);
    freeObj(vec2);
    freeObj(mat2);
    freeObj(mat3);
    freeObj(matMultMV);

    /*double* nVector = (double*)malloc(sizeof(double)*NCOL);
    for (int i=0; i<NCOL; i++) nVector[i] = i+1; */

    // Vector* myVector = toVector(nVector, NCOL, ROW);
    Vector* myVector = zeros(NCOL, ROW);
    Vector* onesVector = ones(NCOL, ROW);
    puts("\nprintVector() zeros");
    double* modVector = makeModifiable(myVector);
    modVector[1] = targ;
    printVector(myVector);

    puts("\nprintVector() zeros");
    printVector(onesVector);

    puts("\nVector sum");
    Vector* vecSum = plus(myVector, onesVector);
    printVector(vecSum);
    freeObj(vecSum);

    int vecIdx = getIndex(myVector, targ);
    printf("\ngetIdx_v for targ %.2f = %d\n", targ, vecIdx);

    puts("\nmatRepr()");
    matRepr(matMinus);

    puts("\nfreeVector()");
    freeObj(myVector);
    freeObj(onesVector);

    puts("\nfreeMatrix()");
    freeMatrix(myMatrix);
    freeMatrix(matSum);
    freeObj(matMinus);
    freeObj(hisMatrix);
    freeMatrix(matMultC);
    freeMatrix(matMultE);
    freeObj(matMultMM);

    puts("\nArgerror");
    argError();

    return 0;
}
