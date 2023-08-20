#include "array.h"

int getLength( Array* array ) {
    int length = 1;
    Node* currentNode = ((Node*)array->head)->next;
    if (currentNode == array->tail) return 0;
    while (currentNode->next->next != NULL) {
        length++;
        currentNode = currentNode->next;
    }
    return length;
}
