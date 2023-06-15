#ifndef _matrix_h
#define _matrix_h


/* 
 * Change this to "array.h" later,
 * or perhaps make a shared library
 */
#include "../array/src/array.h"

/*
 * Define matrix struct with Array objects
 */
typedef struct ArrayMatrix {
    Array** rowsNcols; // all the rows and columns as arrays
    int matSize[2];
    int rows;
    int cols;
    Array (*getElement)(int, int);
    Array* (*getArray)(char*);
    struct ArrayMatrix* (*getSlice)(char*);
} Matrix_A;

/*
 * Define matrix struct with double
 */
typedef struct DoubleMatrix {
    double** rowsNcols; // all the rows and columns as arrays
    int matSize[2];
    int rows;
    int cols;
    double (*getElement)(int, int);
    double* (*getArray)(char*);
    struct DoubleMatrix** (*getSlice)(char*);
} Matrix_d;

/*
 * Function to make a new matrix
 *     -> takes in a static array if float** and creates a matrix off of it
 *     -> arguments could be: ( int rows, int* cols, double** nMatrix )
 *         -> here `int* cols` is the number of elements per row (each row has x columns)
 *         -> it still can be (int numRows, int numCols, double** nMatrix) since
 *              matrices don't have varying row lengths.
 *     -> must assign a function pointer to the *getFrom thing
 *         -> syntax:
 *         ...
 *         Matrix* out = (Matrix*)malloc(sizeof(Matrix));
 *         out->rows = numRows;
 *         out->cols = numCols;
 *         out->getFrom = &functionName;
 *         ...
 *
 *         -> and for the Array** double pointer, every single row and 
 *              column will have its own array representation.
 *              -> it could still be possible to make it a double** as well?
 *              -> perhaps rows already exist, and I just have to make the
 *                  column arrays
 *
 *     -> Also, multiple dispatch may be a bad idea since matrix stuff like invert
 *          will mess with it.
 *         -> Maybe just support add() subtract() constMult() and matMult()
 *
 */
Matrix* makeMatrix( double** nMatrix, int numRows, int numCols );

/*
 * Functions to slice or index
 */


/*
 * Common matrix generators
 */
Matrix* zeros( int numRows, int numCols );
Matrix* ones( int numRows, int numCols );
Matrix* eye( int numRows, int numCols );

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
