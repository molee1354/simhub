#include "array_commonincl.h"

int getIndex_i( Array* array, int num ) {
    iNode* currentNode = ((iNode*)array->head)->next;
    int idx = 0;
    while (currentNode->data != num || currentNode->next != NULL) {
        if (currentNode->data == num) return idx;
        currentNode = currentNode->next;
        idx++;
    }
    return getLength(array)-1;
}
int getIndex_d( Array* array, double num ) {
    dNode* currentNode = ((dNode*)array->head)->next;
    int idx = 0;
    while (currentNode->data != num || currentNode->next != NULL) {
        if (currentNode->data == num) return idx;
        currentNode = currentNode->next;
        idx++;
    }
    return getLength(array)-1;
}
int getIndex_c( Array* array, char num ) {
    cNode* currentNode = ((cNode*)array->head)->next;
    int idx = 0;
    while (currentNode->data != num || currentNode->next != NULL) {
        if (currentNode->data == num) return idx;
        currentNode = currentNode->next;
        idx++;
    }
    return getLength(array)-1;
}

