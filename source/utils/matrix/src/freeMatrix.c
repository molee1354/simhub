#include <stdlib.h>
#include "matrix.h"
#include "_matrix.h"

int freeMatrix( Matrix* matrix ) {
    for (int i = 0; i<matrix->nRows; i++) {
        free(matrix->e[i]);
        matrix->e[i] = NULL;
    }

    free(matrix->e);
    matrix->e = NULL;

    free(matrix);

    return 0;
}
