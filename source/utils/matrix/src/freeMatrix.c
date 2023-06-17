#include <stdlib.h>
#include "matrix.h"
#include "guard.h"

int freeMatrix( Matrix* matrix ) {
    // freeing the vectors seems to free the values in nMatrix->e as well
    for (int i=0; i<matrix->nRows+matrix->nCols ; i++) {
        freeVector( matrix->rowsNcols[i] );
    }
    free(matrix->rowsNcols);
    matrix->rowsNcols = NULL;

    free(matrix->e);
    matrix->e = NULL;

    free(matrix);

    return 0;
}