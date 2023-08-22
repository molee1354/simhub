#include <stdlib.h>
#include "array.h"

void deleteTail_T(Array* array) {
    Node* currentNode = ((Node*)array->head)->next;
    while (currentNode->next->next != NULL) {
        currentNode = currentNode->next;
    }
    free(currentNode->next);
    currentNode->next = NULL;
    array->tail = currentNode;
}
void deleteTail_S(Array* array) {
    sNode* currentNode = ((sNode*)array->head)->next;
    while (currentNode->next->next != NULL) {
        currentNode = currentNode->next;
    }
    free(currentNode->next);
    currentNode->next = NULL;
    array->tail = currentNode;
}
void deleteTail( Array* array ) {
    if (array->type == TokenArray) {
        deleteTail_T(array);
    } else if (array->type == StatementArray) {
        deleteTail_S(array);
    } else {
        return;
    }
}
