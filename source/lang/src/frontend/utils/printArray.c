#include <stdio.h>
#include "array.h"

void printArray_T( Array* array ) {
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
void printArray_S( Array* array ) {
    sNode* currentNode = ((sNode*)array->head)->next;
    printf("[");
    if (currentNode == array->tail) {
        puts("]");
        return;
    }
    while (currentNode->next->next != NULL) {
        printf("{%d}, ",currentNode->stmt.kind);
        currentNode = currentNode->next;
    }
    printf("{%d}]\n",currentNode->stmt.kind);
}

void printArray( Array* array ) {
    if (array->type == TokenArray) {
        printArray_T(array);
    } else if (array->type == StatementArray) {
        printArray_S(array);
    } else {
        return;
    }
}
