#include "array.h"

int getLength_T( Array* array ) {
    int length = 1;
    Node* currentNode = ((Node*)array->head)->next;
    if (currentNode == array->tail) return 0;
    while (currentNode->next->next != NULL) {
        length++;
        currentNode = currentNode->next;
    }
    return length;
}
int getLength_S( Array* array ) {
    int length = 1;
    sNode* currentNode = ((sNode*)array->head)->next;
    if (currentNode == array->tail) return 0;
    while (currentNode->next->next != NULL) {
        length++;
        currentNode = currentNode->next;
    }
    return length;
}
int getLength( Array* array ) {
    if (array->type == TokenArray) {
        return getLength_T(array);
    } else if (array->type == StatementArray) {
        return getLength_S(array);
    } else {
        return 1;
    }
}
