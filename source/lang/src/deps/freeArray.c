#include <stdlib.h>
#include "array.h"

int freeArray( Array* array ) {
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
