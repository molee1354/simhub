#include <stdlib.h>
#include "array.h"

int freeArray_T( Array* array ) {
    while ( ((Node*)array->head)->next->next != NULL ) {
        deleteHead(array);
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

int freeArray_S( Array* array ) {
    while ( ((sNode*)array->head)->next->next != NULL ) {
        deleteHead(array);
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

int freeArray( Array* array ) {
    if (array->type == TokenArray) {
        return freeArray_T(array);
    } else if (array->type == StatementArray) {
        return freeArray_S(array);
    } else {
        return 1;
    }
}
