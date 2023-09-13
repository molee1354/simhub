#include "matrix_commonincl.h"


Matrix* multMat_M( Matrix* mat1, Matrix* mat2 ) {
    if (mat1->nCols != mat2->nRows) {
        printf("The given matrices have invalid size!\n");
        printf("\tMatrix 1 : %dx%d\n", mat1->nRows, mat1->nCols);
        printf("\tMatrix 2 : %dx%d\n", mat2->nRows, mat2->nCols);
        return (Matrix*)NULL;
    }
    Matrix* out = makeMatrix( mat1->nRows, mat2->nCols );
    for (int c = 0; c < mat1->nCols; c++) {
        for (int r = 0; r < mat2->nRows; r++) {
            // calculating the row x column dot product
            int dotSum = 0;
            for (int idx = 0; idx < mat1->nRows; idx++) {
                dotSum += mat1->e[r][idx] * mat2->e[idx][c];
            } out->e[r][c] = dotSum; } }

    return out;
}
Vector* multMat_V( Matrix* mat, Vector* vec ) {
    if (mat->nCols != vec->nEle) {
        printf("The given matrices have invalid size!\n");
        printf("\tMatrix length : %d\n", mat->nCols);
        printf("\tVector height : %d\n", vec->nEle);
        return (Vector*)NULL;
    }
    if (vec->direction == ROW) {
        printf("Invalid vector direction for multiplication operation");
        printf(" : type ROW provided, type COL required\n");
    }
    Vector* out = makeVector( vec->nEle, vec->direction );
    for (int c = 0; c < mat->nCols; c++) {
        for (int r = 0; r < mat->nRows; r++) {
            // calculating the row x column dot product
            int dotSum = 0;
            for (int idx = 0; idx < mat->nRows; idx++) {
                dotSum += mat->e[r][idx] * vec->e[idx];
            } out->e[r] = dotSum; } }
    return out;
}
