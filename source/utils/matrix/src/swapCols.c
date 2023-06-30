#include "matrix.h"
#include "_matrix.h"

void swapCols( Matrix* matrix, int thisCol, int thatCol ) {
    for (int i = 0; i<matrix->nCols; i++) {
        double temp = matrix->e[i][thisCol];
        matrix->e[i][thisCol] = matrix->e[i][thatCol];
        matrix->e[i][thatCol] = temp;
    }
}
