#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "guard.h"


Matrix* getSlice( Matrix* matrix, 
                  int leftBound, int rightBound, 
                  int topBound, int botBound ) {
    if (leftBound < 0 || rightBound > matrix->nCols) {
        puts("Input column bound larger than matrix->nCols!");
        return matrix;
    }
    if (topBound < 0 || botBound > matrix->nRows) {
        puts("Input row bound larger than matrix->nRows!");
        return matrix;
    }
    if (topBound == botBound || rightBound == leftBound) {
        puts("Input bounds cannot be of the same value!");
        return matrix;
    }
    puts("Make sure to free the memory allocated by the getSlice() function call");
    Matrix* out = makeMatrix(botBound-topBound, rightBound-leftBound);

    // low bound input is included, high bound is not included.
    int outIdxRow = 0;
    for (int i = topBound; i < botBound; i++) {
        int outIdxCol = 0;
        for (int j = leftBound; j < rightBound; j++) {
            out->e[outIdxRow][outIdxCol] = matrix->e[i][j];
            outIdxCol++;
        }
        outIdxRow++;
    }    
    return out;
}
