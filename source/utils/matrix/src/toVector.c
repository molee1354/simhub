#include <stdlib.h>
#include "matrix.h"
#include "guard.h"


Vector* toVector( double* nArray, int numElem, vType direction ) {
    Vector* out = (Vector*)malloc(sizeof(Vector)*numElem);
    out->e = nArray;
    out->nEle = numElem;
    out->direction = direction;
    return out;
}
