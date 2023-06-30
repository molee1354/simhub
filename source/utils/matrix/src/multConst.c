#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "_matrix.h"

/*
 * All math operations will create a new matrix
 */
Matrix* multConst_M( Matrix* matrix, double constant ) {
    Matrix* out = makeMatrix( matrix->nRows, matrix->nCols );
    for (int i = 0; i<matrix->nRows; i++) {
        for (int j = 0; j<matrix->nCols; j++) {
            out->e[i][j] = matrix->e[i][j]*constant;
        }
    }
    puts("Make sure to free the memory allocated by the mult_C() function call");
    return out;
}
Vector* multConst_V( Vector* vector, double constant ) {
    Vector* out = makeVector( vector->nEle, vector->direction );
    for (int i = 0; i<vector->nEle; i++) {
        out->e[i] = vector->e[i]*constant;
    }
    puts("Make sure to free the memory allocated by the mult_C() function call");
    return out;
}

