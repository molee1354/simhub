#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "guard.h"

double getVector_ii( Matrix* matrix, int rIdx, int cIdx ) {
    return matrix->e[rIdx][cIdx];
}
Vector* getVector_iA( Matrix* matrix, int rIdx, AllFlag cAll ) {
    if (cAll!=ALL) {
        return (Vector*)NULL; }
    puts("Make sure to free the memory allocated by the getVector() function call");
    Vector* out = makeVector(matrix->nCols, ROW);
    for (int i=0; i<matrix->nCols; i++) {
        out->e[i] = matrix->e[rIdx][i];
    }
    return out;
}
Vector* getVector_Ai( Matrix* matrix, AllFlag rAll, int cIdx ) {
    if (rAll!=ALL) {
        return (Vector*)NULL; }
    puts("Make sure to free the memory allocated by the getVector() function call");
    Vector* out = makeVector(matrix->nRows, COL);
    for (int i=0; i<matrix->nRows; i++) {
        out->e[i] = matrix->e[i][cIdx];
    }
    return out;
}
Matrix* getVector_AA( Matrix* matrix, AllFlag rAll, AllFlag cAll ) {
    if (cAll!=ALL) {
        return (Matrix*)NULL; }
    if (rAll!=ALL) {
        return (Matrix*)NULL; }
    return matrix;
} // returns matrix
