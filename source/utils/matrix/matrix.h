#ifndef _matrix_h
#define _matrix_h

typedef struct Matrix {
    int matSize[2]; // 0 --> row, 1 --> col
    int rows;
    int cols;
    float** elements;
} Matrix;

//TODO -> fix this
int** initMatrix( int row, int col, int array2d[][col] );

Matrix* makeMatrix( int row, int col, float** matPointer );

int* getSize( Matrix* matrix );
int getElement( Matrix* matrix);
void printSize( Matrix* matrix);

Matrix* addMat( Matrix* mat1, Matrix* mat2 );
Matrix* subtractMat( Matrix* mat1, Matrix* mat2 );
Matrix* multiplyMat( Matrix* mat1, Matrix* mat2 );
Matrix* multiplyMatConst( Matrix* matrix, int constant );

Matrix* ones( int row, int col, float** matPointer );
Matrix* zeros( int row, int col, float** matPointer );
Matrix* eye( int size, float** matPointer );

//TODO -> make this
// float determinantMat( Matrix* matrix );
Matrix* inverseMat( Matrix* matrix );
// Matrix* refMat( Matrix* matrix );
// Matrix* rrefMat( Matrix* matrix );

void printMatrix( Matrix* matrix );

#endif
