#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "matrix.h"

#define NROW 3
#define NCOL 4
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

    Matrix* myMatrix = toMatrix(nMatrix, NROW, NCOL);
    puts("\nprintMatrix()");
    printMatrix(myMatrix);

    double* nVector = (double*)malloc(sizeof(double)*NCOL);
    for (int i=0; i<NCOL; i++) nVector[i] = i+1;
     
    Vector* myVector = toVector(nVector, NCOL, ROW);
    puts("\nprintVector()");
    printVector(myVector);

    puts("\nmatRepr()");
    matRepr(myMatrix);

    return 0;
}
