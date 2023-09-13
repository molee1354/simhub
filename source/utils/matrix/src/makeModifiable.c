#include "matrix_commonincl.h"

double** makeModifiable_M( Matrix* matrix ) {
    return matrix->e;
}
double*  makeModifiable_V( Vector* vector ) {
    return vector->e;
}
