#include "matrix.h"
#include "_matrix.h"

void swapRows( Matrix* matrix, int thisRow, int thatRow ) {
    for (int i = 0; i<matrix->nCols; i++) {
        double temp = matrix->e[thisRow][i];
        matrix->e[thisRow][i] = matrix->e[thatRow][i];
        matrix->e[thatRow][i] = temp;
    }
}
