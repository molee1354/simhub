#include "matrix_commonincl.h"

double determinant( Matrix* matrix ) {
    if (matrix->isSquare!=1) {
        puts("Cannot calculate a determinant for a non-square matrix!");
        return -9999.;
    }
    // Base cases
    if (matrix->nRows == 1) {
        return matrix->e[0][0];}
    if (matrix->nRows == 2) {
        return matrix->e[0][0]*matrix->e[1][1]-matrix->e[0][1]*matrix->e[1][0];}

    double det = 0.0;
    int sign = 1;

    // submatrix for cofactors
    Matrix* subMatrix = makeMatrix(matrix->nRows-1, matrix->nCols-1);

    // Iterate over the first row to calculate the determinant
    for (int j = 0; j < matrix->nRows; j++) {
        // Generate the submatrix
        int sub_i = 0;
        for (int i = 1; i < matrix->nRows; i++) {
            int sub_j = 0;
            for (int k = 0; k < matrix->nRows; k++) {
                if (k != j) {
                    subMatrix->e[sub_i][sub_j] = matrix->e[i][k];
                    sub_j++; } }
            sub_i++; }

        // Calculate the determinant recursively
        det += sign * matrix->e[0][j] * determinant(subMatrix);
        sign = -sign;
    }
    freeMatrix(subMatrix);
    return det;
}
