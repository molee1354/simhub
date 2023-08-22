#include <stdlib.h>
#include "array.h"

void deleteHead_T( Array* array ) {
    Node* temp = ((Node*)array->head)->next;
    ((Node*)array->head)->next = temp->next;
    free(temp->token.value);
    free(temp);
    temp = NULL;
}
void deleteHead_S( Array* array ) {
    sNode* temp = ((sNode*)array->head)->next;
    ((sNode*)array->head)->next = temp->next;
    free(temp);
    temp = NULL;
}

void deleteHead( Array* array ) {
    if (array->type == TokenArray) {
        deleteHead_T(array);
    } else if (array->type == StatementArray) {
        deleteHead_S(array);
    } else {
        return;
    }
}
