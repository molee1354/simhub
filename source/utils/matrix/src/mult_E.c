#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "guard.h"

/*
 * All math operations will create a new matrix
 */
Matrix* mult_ME( Matrix* mat1, Matrix* mat2 ) {
    if (mat1->nRows != mat2->nRows ||  mat1->nCols != mat2->nCols) {
        printf("The given matrices are of different size!\n");
        printf("\tMatrix 1 : %dx%d\n", mat1->nRows, mat1->nCols);
        printf("\tMatrix 2 : %dx%d\n", mat2->nRows, mat2->nCols);
        return (Matrix*)NULL;
    }
    Matrix* out = makeMatrix( mat1->nRows, mat1->nCols );
    for (int i = 0; i<mat1->nRows; i++) {
        for (int j = 0; j<mat1->nCols; j++) {
            out->e[i][j] = mat1->e[i][j] * mat2->e[i][j];
        } }
    puts("Make sure to free the memory allocated by the plus() function call");
    return out;
}
Vector* mult_VE( Vector* vec1, Vector* vec2 ) {
    if (vec1->nEle != vec2->nEle || vec1->direction != vec2->direction) {
        printf("The given vectors are of different size!\n");
        printf("\tVector 1 : %dx%d\n", vec1->nEle, vec1->nEle);
        printf("\tVector 2 : %dx%d\n", vec2->nEle, vec2->nEle);
        return (Vector*)NULL;
    }
    Vector* out = makeVector( vec1->nEle, vec1->direction );
    for (int i = 0; i<vec1->nEle; i++) {
        out->e[i] = vec1->e[i] * vec2->e[i];
    }
    puts("Make sure to free the memory allocated by the plus() function call");
    return out;
}

