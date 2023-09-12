#include <stdlib.h>
#include "array.h"
#include "_array.h"

static Array* initArray_i( size_t dtype, int size ) {
    Array* array = makeArray(sizeof(int));
    if (array == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( array, 0 ); }
    return array;
}
static Array* initArray_d( size_t dtype, int size ) {
    Array* array = makeArray(sizeof(double));
    if (array == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( array, 0. ); }
    return array;
}
static Array* initArray_c( size_t dtype, int size ) {
    Array* array = makeArray(sizeof(char));
    if (array == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( array, '\0' ); }
    return array;
}

Array* initArray( size_t dtype, int size ) {
    if (dtype == sizeof(int)) {
        return initArray_i( dtype, size );
    } else if (dtype == sizeof(double)) {
        return initArray_d( dtype, size );
    } else if (dtype == sizeof(char)) {
        return initArray_c( dtype, size );
    } else {
        return NULL;
    }
}

