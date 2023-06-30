#include "matrix.h"
#include "_matrix.h"

int* getSize_M( Matrix* matrix ) {
    return matrix->size;
}
int  getSize_V( Vector* matrix ) {
    return matrix->nEle;
}