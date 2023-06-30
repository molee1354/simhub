#include <stdio.h>
#include "matrix.h"
#include "_matrix.h"

Vector* copyVector(Vector* vector) {
    Vector* out = makeVector(vector->nEle, vector->direction);
    puts("Make sure to free the memory allocated by the copyVector() function call");
    for (int i = 0; i < vector->nEle; i++) {
        out->e[i] = vector->e[i];
    }
    return out;
}
