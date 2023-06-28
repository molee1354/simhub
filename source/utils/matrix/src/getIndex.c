#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "guard.h"

int* getIndex_M( Matrix* matrix, double target ) {
    int* out = (int*)malloc(sizeof(int)*2);
    if (out==NULL) {return NULL;}
    for (int i = 0; i < matrix->nRows; i++) {
        for (int j = 0; j < matrix->nCols; j++) {
            if ( matrix->e[i][j] == target ) {
                out[0] = i; out[1] = j;
                return out;
            } } }
    out[0] = -1;
    out[1] = -1;
    puts("Make sure to free the memory allocated by the getIndex() function call");
    return out;
}
int getIndex_V( Vector* vector, double target ) {
    int out = -1;
    for (int i = 0; i < vector->nEle; i++) {
        if ( vector->e[i] == target ) return i;
    }
    return out;
}