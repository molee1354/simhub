#include <stdio.h>
#include "matrix.h"
#include "_matrix.h"

int printMatrix( Matrix* matrix ) {
    printf("%d x %d matrix\n", matrix->nRows, matrix->nCols);
    printf("[");
    for (int i=0; i<matrix->nRows; i++) {
        printf( (i==0) ? "[" : " [");
        int j;
        for (j=0;j<matrix->nCols-1; j++) {
            printf("%7.3f ", matrix->e[i][j]);
        } printf("%7.3f%s", matrix->e[i][j],
                 (i == matrix->nRows-1) ? " ]" : " ]\n");
    } printf("]\n");
    return 0;
}
