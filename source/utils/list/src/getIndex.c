#include "list_commonincl.h"

int getIndex_i( List* list, int num ) {
    iNode* currentNode = ((iNode*)list->head)->next;
    int idx = 0;
    while (currentNode->data != num || currentNode->next != NULL) {
        if (currentNode->data == num) return idx;
        currentNode = currentNode->next;
        idx++;
    }
    return getLength(list)-1;
}
int getIndex_d( List* list, double num ) {
    dNode* currentNode = ((dNode*)list->head)->next;
    int idx = 0;
    while (currentNode->data != num || currentNode->next != NULL) {
        if (currentNode->data == num) return idx;
        currentNode = currentNode->next;
        idx++;
    }
    return getLength(list)-1;
}
int getIndex_c( List* list, char num ) {
    cNode* currentNode = ((cNode*)list->head)->next;
    int idx = 0;
    while (currentNode->data != num || currentNode->next != NULL) {
        if (currentNode->data == num) return idx;
        currentNode = currentNode->next;
        idx++;
    }
    return getLength(list)-1;
}

