#ifndef _matrix_guard_h
#define _matrix_guard_h

#ifdef NAME_MANGLE
#include "matrix_matrix.h"
#else
#include "matrix.h"
#endif

/*
 * Define vector struct
 *      -> enums used to set direction
 */
typedef struct DoubleVector {
    double* e;
    int nEle;
    vType direction;
} Vector;

/*
 * Define matrix struct with double
 * the length of a row is equal to the number of columns and vice versa
 */
typedef struct DoubleMatrix {
    double** e;
    int nRows;
    int nCols;
    int size[2];
    int isSquare;
} Matrix;

#endif
