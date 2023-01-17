#include<stdio.h>
#include<stdlib.h>

#include "matrix.h"

void doSum() {
    const int row = 3;
    const int col = 3;

    int matNums1[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,0}
    };
    int** array2d_1 = (int**)malloc(sizeof(int*)*row);
    int** array2d_2 = (int**)malloc(sizeof(int*)*row);
    for (int i=0, n=0; i<col; i++) {
        array2d_1[i] = (int*)malloc(sizeof(int)*col);
        array2d_2[i] = (int*)malloc(sizeof(int)*col);
    }
    for (int i=0; i<row; i++) {
        for (int j=0; j<row; j++) {
            array2d_1[i][j] = matNums1[i][j];
            array2d_2[i][j] = matNums1[i][j]+1;
        }
    }
    Matrix* myMat1 = makeMatrix(3,3, array2d_1);
    Matrix* myMat2 = makeMatrix(3,3, array2d_2);

    puts("Matrix 1");
    printMatrix(myMat1);
    puts("\nMatrix 2");
    printMatrix(myMat2);

    puts("\nMatrix addition");
    Matrix* newMat = addMat(myMat1, myMat2);
    printMatrix(newMat);

    for (int i=0; i<row; i++) free(array2d_1[i]);
    free(array2d_1);
    for (int i=0; i<row; i++) free(array2d_2[i]);
    free(array2d_2);

    free(myMat1);
    free(myMat2);
    free(newMat);
}

int doMult() {
    const int dim1 = 9;
    const int dim2 = 2;
    int matNums1[9][9] = {
        {1,2,3,1,2,3,1,2,3},
        {1,2,3,1,2,3,1,2,3},
        {1,2,3,1,2,3,1,2,3},
        {1,2,3,1,2,3,1,2,3},
        {1,2,3,0,2,3,1,2,3},
        {1,2,3,1,2,3,1,2,3},
        {1,2,3,1,2,0,1,2,3},
        {1,2,3,1,2,3,1,2,3},
        {1,2,3,1,2,3,1,2,3}
    };
    int matNums2[9][2] = {
        {7,8},
        {7,8},
        {7,8},
        {7,8},
        {7,8},
        {7,8},
        {7,8},
        {7,8},
        {7,8}
    };

    int** array2d_1 = (int**)malloc(sizeof(int*)*dim1);
    for (int i = 0; i < dim1; i++) array2d_1[i] = (int*)malloc(sizeof(int)*dim1);
    for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim1; j++) array2d_1[i][j] = matNums1[i][j];
    }

    int** array2d_2 = (int**)malloc(sizeof(int*)*dim1);
    for (int i = 0; i < dim1; i++) array2d_2[i] = (int*)malloc(sizeof(int)*dim2);
    for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim2; j++) array2d_2[i][j] = matNums2[i][j];
    }
    
    Matrix* myMat1 = makeMatrix(9,9, array2d_1);
    Matrix* myMat2 = makeMatrix(9,2, array2d_2);

    puts("\nMatrix 1");
    printMatrix(myMat1);
    puts("\nMatrix 2");
    printMatrix(myMat2);

    puts("\nMatrix Multiplication");
    Matrix* newMat = multiplyMat(myMat1, myMat2);
    printMatrix(newMat);

    for (int i=0; i<dim1; i++) free(array2d_1[i]);
    free(array2d_1);
    for (int i=0; i<dim2; i++) free(array2d_2[i]);
    free(array2d_2);

    free(myMat1);
    free(myMat2);
    free(newMat);
}

int main() {
    doMult();

    return 0;
}