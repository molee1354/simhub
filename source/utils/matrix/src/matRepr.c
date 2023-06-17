#include <stdio.h>
#include "matrix.h"
#include "guard.h"


int matRepr( Matrix* matrix ) {

    puts("Matrix structure representation:");
    printf("* {}->nRows : %d\n", matrix->nRows);
    printf("* {}->nCols : %d\n", matrix->nCols);
    printf("* {}->size [r,c] : [%d, %d]\n", matrix->size[0], matrix->size[1] );
    printf("* {}->squareMat : %s\n", (matrix->isSquare==1) ? "yes" : "no");
    printf("\n* {}->e :\n\n");
    printMatrix(matrix);
    printf("\n\n* {}->rowsNcols :\n");
    for (int i=0; i<matrix->nCols+matrix->nRows; i++) {
        if (i<matrix->nRows) printf("\n[%d] -> [%d,:] : ", i, i-matrix->nRows);
        else printf("\n[%d] -> [:,%d] :\n", i, i-matrix->nRows);
        printVector(matrix->rowsNcols[i]);
    }
    return 0;
}
