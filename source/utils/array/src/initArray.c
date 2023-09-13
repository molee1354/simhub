#include "array_commonincl.h"

static Array* initArray_i( int size ) {
    Array* array = makeArray(sizeof(int));
    if (array == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( array, 0 ); }
    return array;
}
static Array* initArray_d( int size ) {
    Array* array = makeArray(sizeof(double));
    if (array == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( array, 0. ); }
    return array;
}
static Array* initArray_c( int size ) {
    Array* array = makeArray(sizeof(char));
    if (array == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( array, '\0' ); }
    return array;
}

Array* initArray( size_t dtype, int size ) {
    if (dtype == sizeof(int)) {
        return initArray_i( size );
    } else if (dtype == sizeof(double)) {
        return initArray_d( size );
    } else if (dtype == sizeof(char)) {
        return initArray_c( size );
    } else {
        return NULL;
    }
}

