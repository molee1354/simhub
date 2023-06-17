#include <stdio.h>
#include "matrix.h"
#include "guard.h"


int matRepr( Matrix* matrix ) {

    puts("Matrix structure representation:");
    printf("\t* {}->nRows : %d\n", matrix->nRows);
    printf("\t* {}->nCols : %d\n", matrix->nCols);
    printf("\t* {}->size [r,c] : [%d, %d]\n", matrix->size[0], matrix->size[1] );
    printf("\t* {}->squareMat : %s\n", (matrix->isSquare==1) ? "yes" : "no");
    printf("\n\t* {}->e :\n\n");
    printMatrix(matrix);
    printf("\n\n\t* {}->rowsNcols :\n");
    for (int i=0; i<matrix->nCols+matrix->nRows; i++) {
        if (i<matrix->nRows) printf("\n[%d] -> [%d,:] : ", i, i-matrix->nRows);
        else printf("\n[%d] -> [:,%d] :\n", i, i-matrix->nRows);
        printVector(matrix->rowsNcols[i]);
    }
    return 0;
}
