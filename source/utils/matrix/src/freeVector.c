#include <stdlib.h>
#include "matrix.h"
#include "_matrix.h"

int freeVector( Vector* vector ) {
    free(vector->e);
    vector->e = NULL;
    free(vector);
    vector = NULL;
    return 0;
}
