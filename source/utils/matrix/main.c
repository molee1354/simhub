#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "matrix.h"

void doSum() {
    const int row = 3;
    const int col = 3;

    float matNums1[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,0}
    };
    float** array2d_1 = (float**)malloc(sizeof(float*)*row);
    float** array2d_2 = (float**)malloc(sizeof(float*)*row);
    for (int i=0, n=0; i<col; i++) {
        array2d_1[i] = (float*)malloc(sizeof(float)*col);
        array2d_2[i] = (float*)malloc(sizeof(float)*col);
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

void doMult() {
    const int dim1 = 9;
    const int dim2 = 2;
    float matNums1[9][9] = {
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
    float matNums2[9][2] = {
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

    float** array2d_1 = (float**)malloc(sizeof(float*)*dim1);
    for (int i = 0; i < dim1; i++) array2d_1[i] = (float*)malloc(sizeof(float)*dim1);
    for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim1; j++) array2d_1[i][j] = matNums1[i][j];
    }

    float** array2d_2 = (float**)malloc(sizeof(float*)*dim1);
    for (int i = 0; i < dim1; i++) array2d_2[i] = (float*)malloc(sizeof(float)*dim2);
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

void doConstMult() {
    const int dim1 = 9;
    const int dim2 = 2;
    float matNums1[9][9] = {
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

    float** array2d_1 = (float**)malloc(sizeof(float*)*dim1);
    for (int i = 0; i < dim1; i++) array2d_1[i] = (float*)malloc(sizeof(float)*dim1);
    for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim1; j++) array2d_1[i][j] = matNums1[i][j];
    }

    Matrix* myMat1 = makeMatrix(9,9, array2d_1);

    puts("\nMatrix 1");
    printMatrix(myMat1);

    puts("\nMatrix constant multiplication");
    Matrix* newMat = multiplyMatConst(myMat1, 2);
    printMatrix(newMat);

    for (int i=0; i<dim1; i++) free(array2d_1[i]);
    free(array2d_1);
    free(myMat1);
}

void makeOnesZeros( char* arg ) {
    const int dim1 = 3;
    const int dim2 = 4;

    float** array2d = (float**)malloc(sizeof(float*)*dim1);
    for (int i = 0; i<dim1; i++) array2d[i] = (float*)malloc(sizeof(float)*dim2);

    Matrix* newMat;
    if ( !strcmp(arg, "ones")) {
        newMat = ones(dim1, dim2, array2d);
    } else {
        newMat = zeros(dim1, dim2, array2d);
    }
    printMatrix(newMat);

    for (int i = 0; i<dim1; i++) free(array2d[i]);
    free(array2d);
    free(newMat);
}

void doIdentity() {
    const int size = 4;

    float** array2d = (float**)malloc(sizeof(float*)*size);
    for (int i = 0; i<size; i++) array2d[i] = (float*)malloc(sizeof(float)*size);

    Matrix* newMat = eye(size, array2d);
    printMatrix(newMat);

    for (int i = 0; i<size; i++) free(array2d[i]);
    free(array2d);
    free(newMat);
}

int main( int argc, char* argv[] ) {
    if (argc > 2) {
        printf("Too many arguments provided.\n");
        return 0;
    }
    if (argc < 2) {
        printf("No arguments provided.\n");
        return 0;
    }

    if ( !strcmp("constmult", argv[1]) ) {
        doConstMult();
    } else if ( !strcmp("matmult", argv[1]) ) {
        doMult();
    } else if ( !strcmp("matsum", argv[1]) ) {
        doSum();
    } else if ( !strcmp("ones", argv[1]) || !strcmp("zeros", argv[1]) ) {
        makeOnesZeros(argv[1]);
    } else if ( !strcmp("eye", argv[1]) ) {
        doIdentity();
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}
