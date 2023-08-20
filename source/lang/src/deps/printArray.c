#include <stdio.h>
#include "array.h"

void printArray( Array* array ) {
    Node* currentNode = ((Node*)array->head)->next;
    printf("[");
    if (currentNode == array->tail) {
        puts("]");
        return;
    }
    while (currentNode->next->next != NULL) {
        printf("{%s: %d}, ",currentNode->token.value, currentNode->token.type);
        currentNode = currentNode->next;
    }
    printf("{%s: %d}]\n",currentNode->token.value, currentNode->token.type);
}
