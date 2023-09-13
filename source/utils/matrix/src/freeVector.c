#include "matrix_commonincl.h"

int freeVector( Vector* vector ) {
    free(vector->e);
    vector->e = NULL;
    free(vector);
    vector = NULL;
    return 0;
}
