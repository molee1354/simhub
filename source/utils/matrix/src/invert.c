#include "matrix_commonincl.h"


Matrix* gaussJordan(Matrix* matrix) {
    Matrix* identity = eye(matrix->nRows);
    for (int i = 0; i < matrix->nRows; i++) {
        if (matrix->e[i][i] == 0) {
            for (int j = i + 1; j < matrix->nRows; j++) {
                if (matrix->e[j][i] != 0) {
                    swapRows(matrix, i, j);
                    swapRows(identity, i, j);
                    break; } } }

        double pivot = matrix->e[i][i];

        // Scale the current row
        for (int j = 0; j < matrix->nRows; j++) {
            matrix->e[i][j] /= pivot;
            identity->e[i][j] /= pivot;
        }

        // Eliminate other rows
        for (int j = 0; j < matrix->nRows; j++) {
            if (j != i) {
                double factor = matrix->e[j][i];
                for (int k = 0; k < matrix->nRows; k++) {
                    matrix->e[j][k] -= factor * matrix->e[i][k];
                    identity->e[j][k] -= factor * identity->e[i][k]; } } } }
    puts("Make sure to free the memory allocated by the invert() function call");
    return identity;
}

/*
 * Function to invert a matrix
 *      -> returns a copy of a matrix for non-invertible cases
 *         to have consistency in function behavior.
 */
Matrix* invert(Matrix* matrix) {
    if (determinant(matrix)==0) {
        puts("Cannot determine the inverse: matrix is singular!");
        return copyMatrix(matrix);
    }
    if (matrix->isSquare!=1) {
        puts("Cannot determine the inverse: matrix is non-square!");
        return copyMatrix(matrix);
    }
    // Perform Gaussian elimination with back substitution
    // gaussJordan(matrix);
    return gaussJordan(matrix);
}
