#ifndef _matrix_h
#define _matrix_h

/* Direction Enum */
typedef enum {
    RowType,
    ColType
} vType;
#define ROW (vType)RowType
#define COL (vType)ColType

/* note: for transpose, flip vType and keep the order
 *      => for [1 2
 *              3 4] --> row 1 = [1 2]; row 2 = [3 4]
 *                       col 1 = [1 3]; col 2 = [2 4]
 *      do transpose, now:
 *      => for [1 3
 *              2 4] --> col 1 = [1 2]; col 2 = [3 4]
 *                       row 1 = [1 3]; row 2 = [2 4]
 */      


/*
 * Declare matrix/vector struct
 */
typedef struct DoubleMatrix Matrix;
typedef struct DoubleVector Vector;

/*
 * Make the matrix modifiable/accessible by index
 */
double*  makeModifiable_V( Vector* vector );
double** makeModifiable_M( Matrix* matrix );
#define makeModifiable( obj ) _Generic( (obj), \
                               Matrix* : makeModifiable_M, \
                               Vector* : makeModifiable_V )(obj)

/*
 * Free modifiable
 */
int freeModifiable_V( double*  vectorDouble, int nElem );
int freeModifiable_M( double** matrixDouble, int nRows );
#define freeModifiable( obj, len ) _Generic( (obj), \
                                    double** : freeModifiable_M, \
                                    double*  : freeModifiable_V )(obj, len)

/*
 * Functions to create a matrix objects
 *      -> toMatrix() receives a double double pointer and makes
 *          a matrix obj based on that
 *      -> makeMatrix() creates a zero matrix of that size
 */
Matrix* toMatrix( double** nMatrix, int numRows, int numCols );
Matrix* makeMatrix( int numRows, int numCols );

/*
 * Functions to create a vector objects
 *      -> toVector() receives a double double pointer and makes
 *          a matrix obj based on that
 *      -> makeVector() creates a zero matrix of that size
 */
Vector* toVector( double* nArray, int numElem, vType direction );
Vector* makeVector( int numElem, vType direction );

/*
 * Function to slice the matrix.
 * Returns a matrix that is within the specified bounds.
 */
Matrix* getSlice( Matrix* matrix, 
                  int leftBound, int rightBound, 
                  int topBound, int botBound 
                );

/*
 * Function to get an individual row or column as a 1d array
 */
typedef enum {
    ALL
} Allflag;
double getVector_ii( Matrix* matrix, int rIdx, int cIdx );
Vector* getVector_iA( Matrix* matrix, int rIdx, Allflag cAll );
Vector* getVector_Ai( Matrix* matrix, Allflag rAll, int cIdx );
Matrix* getVector_AA( Matrix* matrix, Allflag rAll, Allflag cAll ); // returns matrix
#define getVector( rowDef, colDef ) _Generic((rowDef)+(colDef), \
                            int: _Generic( (colDef), \
                                         int: getVector_ii, \
                                     Allflag: getVector_iA ), \
                        Allflag: _Generic( (colDef), \
                                         int: getVector_Ai, \
                                     Allflag: getVector_AA ))(rowDef, colDef)


/*
 * Common matrix/vector generators
 */
/* Creates a matrix/vector of only ones */
Matrix* zeros_M( int numRows, int numCols );
Vector* zeros_V( int numEle, vType direction );
#define zeros( argLen, arg2 ) _Generic( (arg2), \
                               int : zeros_M, \
                             vType : zeros_V )( argLen, arg2 )

/* Creates a matrix/vector of only ones */
Matrix* ones_M( int numRows, int numCols );
Vector* ones_V( int numEle, vType direction );
#define ones( argLen, arg2 ) _Generic( (arg2), \
                               int : ones_M, \
                             vType : ones_V )( argLen, arg2 )

/* creates an identity matrix (only square) */
Matrix* eye( int sideLength ); 

/*
 * 'get' type functions
 */
int* getSize_M( Matrix* matrix );
int getElement_M( Matrix* matrix, int rIdx, int cIdx );
int getIndex_M( Matrix* matrix, double target );
int getRank( Matrix* matrix );

/*
 * Function to change a specific value at the index
 */
int setIndex_M( Matrix* matrix, double element, ...);
int setIndex_V( Vector* matrix, double element, ...);
#define setIndex( obj1, obj2, ... ) _Generic( (obj1), \
                            Matrix* : setIndex_M, \
                            Vector* : setIndex_V )(obj1, obj2, __VA_ARGS__)

/*
 * simple matrix math
 */
Matrix* plus_M( Matrix* mat1, Matrix* mat2 );
Vector* plus_V( Vector* mat1, Vector* mat2 );
#define plus( obj1, obj2 ) _Generic( (obj1)+(obj2), \
                            Matrix* : plus_M, \
                            Vector* : plus_V )(obj1, obj2)

Matrix* minus_M( Matrix* mat1, Matrix* mat2 );
Vector* minus_V( Vector* mat1, Vector* mat2 );
#define minus( obj1, obj2 ) _Generic( (obj1)+(obj2), \
                             Matrix* : minus_M, \
                             Vector* : minus_V )(obj1, obj2)


/*
 * more complex matrix math
 *
 *      ** multiple dispatch not implemented **
 *      -> mult : classic matrix multiplication between 2 matrices
 *          -> for (Matrix*, Matrix*) args, wraps mult_MM() 
 *          -> for (Vector*, Vector*) args, wraps mult_VE()
 *          -> for (Matrix*, Vector*) args, wraps mult_MV()
 *      -> mult_MV : matrix*vector multiplication
 *
 *      ** multiple dispatch implemented **
 *      -> mult_ME : element-wise multiplication between 2 matrices
 *      -> mult_MC : matrix constant multiplication
 *
 */
Matrix* mult_MM( Matrix* mat1, Matrix* mat2 );
Matrix* mult_MV( Matrix* mat, Vector* vec );

Matrix* mult_ME( Matrix* mat1, Matrix* mat2 );
Vector* mult_VE( Vector* vec1, Vector* vec2 );
#define mult_E( obj1, obj2 ) _Generic( (obj1)+(obj2), \
                              Matrix* : mult_ME, \
                              Vector* : mult_VE )(obj1, obj2)

Matrix* mult_MC( Matrix* matrix, double constant );
Vector* mult_VC( Vector* vec1, double constant );
#define mult_C( obj1, obj2 ) _Generic( (obj1)+(obj2), \
                              Matrix* : mult_MC, \
                              Vector* : mult_VC )(obj1, obj2)

/* 
 * function to handle argument input errors
 */
void argError(void);

#define mult(obj1, obj2) _Generic( (obj1)+(obj2),      \
                            Matrix*: _Generic( (obj2),   \
                                     Matrix*: mult_MM,   \
                                     Vector*: mult_MV,   \
                                      double: mult_MC ), \
                            Vector*: _Generic( (obj2),   \
                                     Matrix*: argError,  \
                                     Vector*: mult_VE,   \
                                      double: mult_VC ), \
                            default: argError )(obj1, obj2)

/*
 * Switching
 */
void switchRows( Matrix* matrix, int thisRow, int thatRow );
void switchCols( Matrix* matrix, int thisCol, int thatCol );

/*
 * Other important matrix operations
 */
double determinantMat( Matrix* matrix );
Matrix* invertMat( Matrix* matrix );
Matrix* refMat( Matrix* matrix );
Matrix* rrefMat( Matrix* matrix );
void transpose_V( Vector* vector );
void transpose_M( Matrix* matrix );
#define transpose(obj) _Generic( (obj), \
                        Matrix* : transpose_M, \
                        Vector* : transpose_V )(obj)

/*
 * Printing
 */
int printMatrix( Matrix* matrix );
int printVector( Vector* vector );

/*
 * Representing the matrix object fully
 */
int matRepr( Matrix* matrix );

/*
 * freeing memory
 */
int freeMatrix( Matrix* matrix );
int freeVector( Vector* vector );
#define freeObj(obj) _Generic( (obj), \
                        Matrix* : freeMatrix, \
                        Vector* : freeVector )(obj)

#endif
