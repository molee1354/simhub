#include<stdio.h>
#include<stdlib.h>

#include "matrix.h"

Matrix* makeMatrix( int row, int col, int** matPointer ) {

    Matrix* out = (Matrix*)malloc(sizeof(Matrix*));
    out->elements = matPointer;
    out->matSize[0] = row;
    out->matSize[1] = col;

    return out;
}

int* getSize( Matrix* matrix ) {
    return matrix->matSize;
}

Matrix* addMat( Matrix* mat1, Matrix* mat2 ) {
    if (mat1->matSize[0] != mat2->matSize[0] ||  mat1->matSize[1] != mat2->matSize[1]) {
        printf("The given matrices are of different size!\n");
        printf("\tMatrix 1 : %dx%d\n", mat1->matSize[0], mat1->matSize[1]);
        printf("\tMatrix 2 : %dx%d\n", mat2->matSize[0], mat2->matSize[1]);
        return (Matrix*)NULL;
    }

    int** outPtr = (int**)malloc(sizeof(int*)*mat1->matSize[0]);
    for (int i = 0; i < mat1->matSize[0]; i++) {
        outPtr[i] = (int*)malloc(sizeof(int)*mat1->matSize[1]);
    }
    Matrix* out = makeMatrix( mat1->matSize[0], mat1->matSize[1], outPtr );
    for (int i = 0; i<mat1->matSize[0]; i++) {
        for (int j = 0; j<mat1->matSize[1]; j++) {
            out->elements[i][j] = mat1->elements[i][j] + mat2->elements[i][j];
        }
    }

    return out;
}

Matrix* subtractMat( Matrix* mat1, Matrix* mat2 ) {
    if (mat1->matSize[0] != mat2->matSize[0] ||  mat1->matSize[1] != mat2->matSize[1]) {
        printf("The given matrices are of different size!\n");
        printf("\tMatrix 1 : %dx%d\n", mat1->matSize[0], mat1->matSize[1]);
        printf("\tMatrix 2 : %dx%d\n", mat2->matSize[0], mat2->matSize[1]);
        return (Matrix*)NULL;
    }

    int** outPtr = (int**)malloc(sizeof(int*)*mat1->matSize[0]);
    for (int i = 0; i < mat1->matSize[0]; i++) {
        outPtr[i] = (int*)malloc(sizeof(int)*mat1->matSize[1]);
    }
    Matrix* out = makeMatrix( mat1->matSize[0], mat1->matSize[1], outPtr );
    for (int i = 0; i<mat1->matSize[0]; i++) {
        for (int j = 0; j<mat1->matSize[1]; j++) {
            out->elements[i][j] = mat1->elements[i][j] - mat2->elements[i][j];
        }
    }

    return out;
}

void printMatrix( Matrix* matrix ) {
    printf("[");
    for (int i = 0; i<matrix->matSize[0]; i++) {
        printf("[");
        for (int j = 0; j<matrix->matSize[1]; j++) {
            printf("%d ",matrix->elements[i][j]);
        }
        if (i < 2) printf("\b]\n"); else printf("\b]");
    }
    printf("]\n");

}