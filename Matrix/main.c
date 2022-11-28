#include<stdio.h>
#include<stdlib.h>

#include "matrix.h"

int main() {
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