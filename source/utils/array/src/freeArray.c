#include <stdlib.h>
#include "array.h"
#include "_array.h"

int freeArray_i( Array* array ) {
    while ( ((iNode*)array->head)->next->next != NULL ) {
        deleteHead_i(array);
        continue;
    }
    free(array->head);
    array->head = NULL;
    free(array->tail);
    array->tail = NULL;
    free(array);
    array = NULL;
    return 0;
}
int freeArray_d( Array* array ) {
    while ( ((dNode*)array->head)->next != array->tail) {
        deleteHead_d(array);
        continue;
    }
    free(array->head);
    array->head = NULL;
    free(array->tail);
    array->tail = NULL;
    free(array);
    array = NULL;
    return 0;
}
int freeArray_c( Array* array ) {
    while ( ((cNode*)array->head)->next != array->tail) {
        deleteHead_c(array);
        continue;
    }
    free(array->head);
    array->head = NULL;
    free(array->tail);
    array->tail = NULL;
    free(array);
    array = NULL;
    return 0;
}
int freeArray( Array* array ){
    if (array->dtype == sizeof(int))    return freeArray_i(array);
    if (array->dtype == sizeof(double)) return freeArray_d(array);
    if (array->dtype == sizeof(char))   return freeArray_c(array);
    return 1;
}
