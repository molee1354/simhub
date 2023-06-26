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
    AllType
} AllFlag;
#define ALL (AllFlag)AllType
double getVector_ii( Matrix* matrix, int rIdx, int cIdx );
Vector* getVector_iA( Matrix* matrix, int rIdx, AllFlag cAll );
Vector* getVector_Ai( Matrix* matrix, AllFlag rAll, int cIdx );
Matrix* getVector_AA( Matrix* matrix, AllFlag rAll, AllFlag cAll ); // returns matrix
#define getVector( matrix, rowDef, colDef ) _Generic( (rowDef), \
                               int: _Generic( (colDef), \
                                         int: getVector_ii, \
                                     AllFlag: getVector_iA ), \
                           AllFlag: _Generic( (colDef), \
                                         int: getVector_Ai, \
                                     AllFlag: getVector_AA ))(matrix, rowDef, colDef)


/*
 * Common matrix/vector generators
 */
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
int  getSize_V( Vector* vector );
#define getSize( obj ) _Generic( (obj), \
                        Matrix* : getSize_M, \
                        Vector* : getSize_V )( obj )

/*
 * This function won't be implemented as the makeModifiable()
 * function pretty much has the same function, and seems to be
 * easier/more intuitive
 */
int getElement_M( Matrix* matrix, int rIdx, int cIdx );
int getRank( Matrix* matrix );
/* No implementation */
int* setIndex_M( Matrix* matrix, double element, ...);
int  setIndex_V( Vector* matrix, double element, ...);
#define setIndex( obj1, obj2, ... ) _Generic( (obj1), \
        Matrix* : setIndex_M, \
        Vector* : setIndex_V )(obj1, obj2, __VA_ARGS__)


/*
 * getting the index of the first occurence
 */
int* getIndex_M( Matrix* matrix, double target );
int  getIndex_V( Vector* matrix, double target );
#define getIndex( obj, targ ) _Generic( (obj), \
                        Matrix* : getIndex_M, \
                        Vector* : getIndex_V )( obj, targ )

/* 
 * function to handle argument input errors
 */
void argError(void);

/*
 * simple matrix math
 */
Matrix* plus_M( Matrix* mat1, Matrix* mat2 );
Vector* plus_V( Vector* mat1, Vector* mat2 );
#define plus(obj1, obj2) _Generic( (obj1), \
                          Matrix*: _Generic((obj2), \
                                   Matrix*: plus_M, \
                                   Vector*: argError), \
                          Vector*: _Generic((obj2), \
                                   Matrix*: argError, \
                                   Vector*: plus_V ), \
                          default: argError )(obj1, obj2)


Matrix* minus_M( Matrix* mat1, Matrix* mat2 );
Vector* minus_V( Vector* mat1, Vector* mat2 );
#define minus(obj1, obj2) _Generic( (obj1), \
                          Matrix*: _Generic((obj2), \
                                   Matrix*: minus_M, \
                                   Vector*: argError), \
                          Vector*: _Generic((obj2), \
                                   Matrix*: argError, \
                                   Vector*: minus_V ), \
                          default: argError )(obj1, obj2)


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
Vector* mult_MV( Matrix* mat, Vector* vec );

Matrix* mult_ME( Matrix* mat1, Matrix* mat2 );
Vector* mult_VE( Vector* vec1, Vector* vec2 );
#define mult_E(obj1, obj2) _Generic((obj1), \
                            Matrix*: _Generic((obj2), \
                                    Matrix*: mult_ME, \
                                    Vector*: argError), \
                            Vector*: _Generic((obj2), \
                                    Matrix*: argError, \
                                    Vector*: mult_VE, \
                                    default: argError))(obj1, obj2)


Matrix* mult_MC( Matrix* matrix, double constant );
Vector* mult_VC( Vector* vec1, double constant );
#define mult_C(obj1, obj2) _Generic((obj1), \
                            Matrix*: mult_MC, \
                            Vector*: mult_MV, \
                            default: argError )(obj1, obj2)

#define mult(obj1, obj2) _Generic( (obj1),      \
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
double determinant( Matrix* matrix );
Matrix* invert( Matrix* matrix );
Matrix* ref( Matrix* matrix );
Matrix* rref( Matrix* matrix );
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
#define printObj(obj) _Generic( (obj), \
                        Matrix* : printMatrix, \
                        Vector* : printVector, \
                        default : argError )(obj)

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
                        Vector* : freeVector, \
                        default : argError )(obj)
/*
 * freeing multiple instances --> they have to be of the same type
 */
int freeAll_M( Matrix* first, ...);
int freeAll_V( Vector* first, ...);

#endif
