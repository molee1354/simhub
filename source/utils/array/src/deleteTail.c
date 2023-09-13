#include "array_commonincl.h"

void deleteTail_i(Array* array) {
    iNode* currentNode = ((iNode*)array->head)->next;
    while (currentNode->next->next != NULL) {
        currentNode = currentNode->next;
    }
    free(currentNode->next);
    currentNode->next = NULL;
    array->tail = currentNode;
}
void deleteTail_d(Array* array) {
    dNode* currentNode = ((dNode*)array->head)->next;
    while (currentNode->next->next != NULL) {
        currentNode = currentNode->next;
    }
    free(currentNode->next);
    currentNode->next = NULL;
    array->tail = currentNode;
}
void deleteTail_c(Array* array) {
    cNode* currentNode = ((cNode*)array->head)->next;
    while (currentNode->next->next != NULL) {
        currentNode = currentNode->next;
    }
    free(currentNode->next);
    currentNode->next = NULL;
    array->tail = currentNode;
}
void deleteTail( Array* array ){
    if (array->dtype == sizeof(int))    deleteTail_i(array);
    if (array->dtype == sizeof(double)) deleteTail_d(array);
    if (array->dtype == sizeof(char))   deleteTail_c(array);
}

