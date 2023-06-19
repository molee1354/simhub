#include <stdio.h>
#include "matrix.h"
#include "guard.h"

int printVector( Vector* vector ) {
    if (vector->direction == ROW) {
        printf("%d element row vector\n", vector->nEle);
        printf("[ ");
        int i;
        for (i=0; i<vector->nEle-1; i++) {
            printf("%7.3f ", vector->e[i]);
        } printf("%7.3f ]\n", vector->e[i]);
    } else {
        printf("%d element col vector\n", vector->nEle);
        int i;
        for (i=0; i<vector->nEle; i++) {
            printf("|%7.3f |\n", vector->e[i]);
        }
    }

    return 0;
}
