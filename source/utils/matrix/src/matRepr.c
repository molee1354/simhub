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

    // Row representation
    for (int i=0; i<matrix->nRows; i++) {
        printf(" Row %d [%d,:] : \n[", i, i);
        int j;
        for (j=0;j<matrix->nCols-1; j++) {
            printf("%7.3f, ", matrix->e[i][j]);
        }   printf("%7.3f]\n\n", matrix->e[i][j]);
    }

    // Column representation
    for (int i=0; i<matrix->nCols; i++) {
        printf(" Col %d [:,%d] : \n", i, i);
        int j;
        for (j=0;j<matrix->nRows-1; j++) {
            printf("| %7.3f |\n", matrix->e[j][i]);
        }   printf("| %7.3f |\n\n", matrix->e[j][i]);
    }
    return 0;
}
