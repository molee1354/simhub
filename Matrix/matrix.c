#include<stdio.h>
#include<stdlib.h>

#include "matrix.h"

int** initMatrix( int row, int col, int array2d[][col] ) {

    int** out = (int**)malloc(sizeof(int*)*row);
    for (int i = 0; i < row; i++) {
        out[i] = (int*)malloc(sizeof(int)*col);
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            out[i][j] = array2d[i][j];
        }
    }

    return out;
}

Matrix* makeMatrix( int row, int col, int** matPointer ) {

    Matrix* out = (Matrix*)malloc(sizeof(Matrix*));
    out->elements = matPointer;
    out->matSize[0] = row;
    out->matSize[1] = col;
    out->rows = row;
    out->cols = col;

    return out;
}

int* getSize( Matrix* matrix ) {
    return matrix->matSize;
}

void printSize( Matrix* matrix ) {
    printf("[row,col] --> [%d,%d]\n", matrix->rows, matrix->cols);
}

Matrix* addMat( Matrix* mat1, Matrix* mat2 ) {
    // error case
    if (mat1->rows != mat2->rows ||  mat1->cols != mat2->cols) {
        printf("The given matrices are of different size!\n");
        printf("\tMatrix 1 : %dx%d\n", mat1->rows, mat1->cols);
        printf("\tMatrix 2 : %dx%d\n", mat2->rows, mat2->cols);
        return (Matrix*)NULL;
    }

    int** outPtr = (int**)malloc(sizeof(int*)*mat1->rows);
    for (int i = 0; i < mat1->rows; i++) {
        outPtr[i] = (int*)malloc(sizeof(int)*mat1->cols);
    }
    Matrix* out = makeMatrix( mat1->rows, mat1->cols, outPtr );
    for (int i = 0; i<mat1->rows; i++) {
        for (int j = 0; j<mat1->cols; j++) {
            out->elements[i][j] = mat1->elements[i][j] + mat2->elements[i][j];
        }
    }

    return out;
}

Matrix* subtractMat( Matrix* mat1, Matrix* mat2 ) {
    // error case
    if (mat1->rows != mat2->rows ||  mat1->cols != mat2->cols) {
        printf("The given matrices are of different size!\n");
        printf("\tMatrix 1 : %dx%d\n", mat1->rows, mat1->cols);
        printf("\tMatrix 2 : %dx%d\n", mat2->rows, mat2->cols);
        return (Matrix*)NULL;
    }

    int** outPtr = (int**)malloc(sizeof(int*)*mat1->rows);
    for (int i = 0; i < mat1->rows; i++) {
        outPtr[i] = (int*)malloc(sizeof(int)*mat1->cols);
    }
    Matrix* out = makeMatrix( mat1->rows, mat1->cols, outPtr );
    for (int i = 0; i<mat1->rows; i++) {
        for (int j = 0; j<mat1->cols; j++) {
            out->elements[i][j] = mat1->elements[i][j] - mat2->elements[i][j];
        }
    }

    return out;
}

Matrix* multiplyMat( Matrix* mat1, Matrix* mat2 ) {
    // error case
    if (mat1->cols != mat2->rows) {
        printf("The given matrices have invalid size!\n");
        printf("\tMatrix 1 : %dx%d\n", mat1->rows, mat1->cols);
        printf("\tMatrix 2 : %dx%d\n", mat2->rows, mat2->cols);
        return (Matrix*)NULL;
    }

    int** outPtr = (int**)malloc(sizeof(int*)*mat2->rows);
    for (int i = 0; i < mat1->rows; i++) {
        outPtr[i] = (int*)malloc(sizeof(int)*mat1->cols);
    }

    Matrix* out = makeMatrix( mat1->rows, mat2->cols, outPtr );
    for (int c = 0; c < mat1->cols; c++) {
        for (int r = 0; r < mat2->rows; r++) {

            // calculating the row x column dot product
            int dotSum = 0;
            for (int idx = 0; idx < mat1->rows; idx++) {
                dotSum += mat1->elements[r][idx] * mat2->elements[idx][c];
            }
            out->elements[r][c] = dotSum;
        }
    }

    return out;
}

void printMatrix( Matrix* matrix ) {
    printf("[");
    for (int i = 0; i<matrix->rows; i++) {
        printf("[");
        for (int j = 0; j<matrix->cols; j++) {
            printf("%d ",matrix->elements[i][j]);
        }
        if (i < matrix->rows-1) printf("\b]\n"); else printf("\b]");
    }
    printf("]\n");

}