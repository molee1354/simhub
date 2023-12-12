#include "list_commonincl.h"

int getLength_i( List* list ) {
    int length = 1;
    iNode* currentNode = ((iNode*)list->head)->next;
    if (currentNode == list->tail) return 0;
    while (currentNode->next->next != NULL) {
        length++;
        currentNode = currentNode->next;
    }
    return length;
}
int getLength_d( List* list ) {
    int length = 1;
    dNode* currentNode = ((dNode*)list->head)->next;
    if (currentNode == list->tail) return 0;
    while (currentNode->next->next != NULL) {
        length++;
        currentNode = currentNode->next;
    }
    return length;
}
int getLength_c( List* list ) {
    int length = 1;
    cNode* currentNode = ((cNode*)list->head)->next;
    if (currentNode == list->tail) return 0;
    while (currentNode->next->next != NULL) {
        length++;
        currentNode = currentNode->next;
    }
    return length;
}
int getLength( List* list ){
    if (list->dtype == sizeof(int))    return getLength_i(list);
    if (list->dtype == sizeof(double)) return getLength_d(list);
    if (list->dtype == sizeof(char))   return getLength_c(list);
    return 1;
}
