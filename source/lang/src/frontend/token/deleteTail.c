#include <stdlib.h>
#include "array.h"

void deleteTail(Array* array) {
    Node* currentNode = ((Node*)array->head)->next;
    while (currentNode->next->next != NULL) {
        currentNode = currentNode->next;
    }
    free(currentNode->next);
    currentNode->next = NULL;
    array->tail = currentNode;
}
