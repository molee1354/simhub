#include "list_commonincl.h"

void deleteTail_i(List* list) {
    iNode* currentNode = ((iNode*)list->head)->next;
    while (currentNode->next->next != NULL) {
        currentNode = currentNode->next;
    }
    free(currentNode->next);
    currentNode->next = NULL;
    list->tail = currentNode;
}
void deleteTail_d(List* list) {
    dNode* currentNode = ((dNode*)list->head)->next;
    while (currentNode->next->next != NULL) {
        currentNode = currentNode->next;
    }
    free(currentNode->next);
    currentNode->next = NULL;
    list->tail = currentNode;
}
void deleteTail_c(List* list) {
    cNode* currentNode = ((cNode*)list->head)->next;
    while (currentNode->next->next != NULL) {
        currentNode = currentNode->next;
    }
    free(currentNode->next);
    currentNode->next = NULL;
    list->tail = currentNode;
}
void deleteTail( List* list ){
    if (list->dtype == sizeof(int))    deleteTail_i(list);
    if (list->dtype == sizeof(double)) deleteTail_d(list);
    if (list->dtype == sizeof(char))   deleteTail_c(list);
}

