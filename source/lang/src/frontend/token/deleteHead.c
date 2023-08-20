#include <stdlib.h>
#include "array.h"

void deleteHead( Array* array ) {
    Node* temp = ((Node*)array->head)->next;
    ((Node*)array->head)->next = temp->next;
    free(temp->token.value);
    free(temp);
    temp = NULL;
}
