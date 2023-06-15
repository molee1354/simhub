#include <stdlib.h>
#include "array.h"
#include "guard.h"

Array* toArray_i( int* nArray, int size ) {
    Array* array = makeArray(sizeof(int));
    if (array == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( array, nArray[i] ); }
    return array;
}
Array* toArray_d( double* nArray, int size ) {
    Array* array = makeArray(sizeof(double));
    if (array == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( array, nArray[i] ); }
    return array;
}
Array* toArray_c( char* nArray, int size ) {
    Array* array = makeArray(sizeof(char));
    if (array == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( array, nArray[i] ); }
    return array;
}

