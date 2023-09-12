#include <stdlib.h>
#include "array.h"
#include "_array.h"

static Array* onesArray_i( size_t dtype, int size ) {
    Array* array = makeArray(sizeof(int));
    if (array == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( array, 1 ); }
    return array;
}
static Array* onesArray_d( size_t dtype, int size ) {
    Array* array = makeArray(sizeof(double));
    if (array == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( array, 1. ); }
    return array;
}
static Array* onesArray_c( size_t dtype, int size ) {
    Array* array = makeArray(sizeof(char));
    if (array == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( array, '1' ); }
    return array;
}

Array* onesArray( size_t dtype, int size ) {
    if (dtype == sizeof(int)) {
        return onesArray_i( dtype, size );
    } else if (dtype == sizeof(double)) {
        return onesArray_d( dtype, size );
    } else if (dtype == sizeof(char)) {
        return onesArray_c( dtype, size );
    } else {
        return NULL;
    }
}

