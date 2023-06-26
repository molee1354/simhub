#include <stdio.h>
#include "matrix.h"
#include "guard.h"

Matrix* copyMatrix(Matrix* matrix) {
    Matrix* out = makeMatrix(matrix->nRows, matrix->nCols);
    puts("Make sure to free the memory allocated by the copyMatrix() function call");
    for (int i = 0; i < matrix->nRows; i++) {
        for (int j = 0; j < matrix->nCols; j++) {
            out->e[i][j] = matrix->e[i][j];
        }
    }
    return out;
}