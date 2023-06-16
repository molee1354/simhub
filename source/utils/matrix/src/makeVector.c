#include <stdlib.h>
#include "matrix.h"
#include "guard.h"

Vector* makeVector( int numElem, vType direction ) {
    Vector* out = (Vector*)malloc(sizeof(Vector));
    double* zeroVector = (double*)calloc(numElem, sizeof(double));
    out->e = zeroVector;
    out->nEle = numElem;
    out->direction = direction;
    return out;
}
