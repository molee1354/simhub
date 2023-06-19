#include <stdlib.h>
#include "matrix.h"
#include "guard.h"

int freeModifiable_M( double** matrix, int nRows ) {
    for (int i = 0; i < nRows; i++) {
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix); 
    matrix = NULL;
    return 0;
}
int freeModifiable_V( double* vector, int nElem ) {
    free(vector);
    vector = NULL;
    return 0;
}