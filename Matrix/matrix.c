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

Matrix* makeMatrix( int row, int col, float** matPointer ) {

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

void freeMatrix( Matrix* matPointer ) {

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

    float** outPtr = (float**)malloc(sizeof(float*)*mat1->rows);
    for (int i = 0; i < mat1->rows; i++) {
        outPtr[i] = (float*)malloc(sizeof(float)*mat1->cols);
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

    float** outPtr = (float**)malloc(sizeof(float*)*mat1->rows);
    for (int i = 0; i < mat1->rows; i++) {
        outPtr[i] = (float*)malloc(sizeof(float)*mat1->cols);
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

    float** outPtr = (float**)malloc(sizeof(float*)*mat2->rows);
    for (int i = 0; i < mat1->rows; i++) {
        outPtr[i] = (float*)malloc(sizeof(float)*mat1->cols);
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

Matrix* multiplyMatConst( Matrix* matrix, int constant ) {
    for (int i = 0; i < matrix->rows; i++ ) {
        for (int j = 0; j < matrix->cols; j++ ) {
            matrix->elements[i][j] = matrix->elements[i][j]*constant;
        }
    }

    return matrix;
}

Matrix* ones( int row, int col, float** matPointer ) {
    Matrix* out = makeMatrix(row, col, matPointer);
    for (int i = 0; i<row; i++) {
        for (int j = 0; j<col; j++) out->elements[i][j] = 1; 
    }

    return out;
}

Matrix* zeros( int row, int col, float** matPointer ) {
    Matrix* out = makeMatrix(row, col, matPointer);
    for (int i = 0; i<row; i++) {
        for (int j = 0; j<col; j++) out->elements[i][j] = 0; 
    }

    return out;
}

Matrix* eye( int size, float** matPointer ) {
    Matrix* out = makeMatrix( size, size, matPointer );
    for (int i = 0; i<size; i++) {
        for (int j = 0; j<size; j++) {
            if (i == j) out->elements[i][j] = 1;
            else out->elements[i][j] = 0;
        }
    }

    return out;
}

// helper function to swap rows within a matrix
void swapRows( Matrix* matrix, int i, int j, int n ) {
    int k;
    float temp;
    for (k = 0; k<n; k++) {
        temp = matrix->elements[i][k];
        matrix->elements[i][k] = matrix->elements[j][k];
        matrix->elements[j][k] = temp;
    }
}

Matrix* inverseMat( Matrix* matrix ) {
    const int size = matrix->rows;
    float ratio;
    int i, j, k, n;

    float** array2d = (float**)malloc(sizeof(float*)*size);
    for (int i = 0; i<size; i++) array2d[i] = (float*)malloc(sizeof(float)*size);
    Matrix* eyeMatrix = eye( size, array2d );

    for (int i = 0; i < size; i++) {
        if (matrix->elements[i][i] == 0) {
            for (j = i+1; j<size; j++) {
                return 0;
            }
        }
    }
}

void printMatrix( Matrix* matrix ) {
    printf("[");
    for (int i = 0; i<matrix->rows; i++) {
        printf("[");
        for (int j = 0; j<matrix->cols; j++) {
            printf("%.3f ",matrix->elements[i][j]);
        }
        if (i < matrix->rows-1) printf("\b]\n"); else printf("\b]");
    }
    printf("]\n");

}
