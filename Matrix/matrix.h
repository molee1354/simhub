#ifndef _matrix_h
#define _matrix_h

typedef struct Matrix {
    int matSize[2];
    int** elements;
} Matrix;

Matrix* makeMatrix( int row, int col, int** matPointer );

int* getSize( Matrix* matrix );

Matrix* addMat( Matrix* mat1, Matrix* mat2 );
Matrix* subtractMat( Matrix* mat1, Matrix* mat2 );
// Matrix* multiplyMat( Matrix* mat1, Matrix* mat2 );

void printMatrix( Matrix* matrix );

#endif