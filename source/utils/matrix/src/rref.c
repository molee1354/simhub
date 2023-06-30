#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "_matrix.h"

Matrix* rref(Matrix* matrix) {
    Matrix* out = copyMatrix(matrix);
    int numRows = out->nRows;
    int numCols = out->nCols;
    
    int lead = 0;
    for (int r = 0; r < numRows; r++) {
        printf("oper : ");
        printMatrix(out);
        if (lead >= numCols) {
            break;
        }
        
        int i = r;
        while (out->e[i][lead] == 0) {
            i++;
            if (i == numRows) {
                i = r;
                lead++;
                if (lead == numCols) {
                    break;
                }
            }
        }
        
        if (lead < numCols) {
            swapRows(out, i, r);
            double div = out->e[r][lead];
            for (int j = 0; j < numCols; j++) {
                out->e[r][j] /= div;
            }
            
            for (int k = 0; k < numRows; k++) {
                if (k != r) {
                    double mult = out->e[k][lead];
                    for (int j = 0; j < numCols; j++) {
                        out->e[k][j] -= mult * out->e[r][j];
                    }
                }
            }
        }
        
        lead++;
    }
    
    return out;
}
