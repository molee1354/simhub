#ifndef _matrix_h
#define _matrix_h

typedef struct Matrix {
    int matSize[2]; // 0 --> row, 1 --> col
    int rows;
    int cols;
    float** elements;
} Obsolete;

/*
 * New Stuff
 */
typedef struct BetterMatrix {
    Array** rowsNcols; // all the rows and columns as arrays
    int matSize[2];
    int rows;
    int cols;
    double (*getFrom)(char*);
} Matrix;

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
 */

/* new stuff above */

//TODO -> fix this
int** initMatrix( int row, int col, int array2d[][col] );

Matrix* old_makeMatrix( int row, int col, float** matPointer );

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
