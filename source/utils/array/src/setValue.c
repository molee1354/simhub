#include "array.h"
#include "_array.h"

iNode* getNode_i( Array* array, int index ) {
    int count = 0;
    iNode* currentNode = (iNode*)array->head;
    while (count <= index) {
        currentNode = currentNode->next;
        count++;
    }
    return currentNode;
}
dNode* getNode_d( Array* array, int index ) {
    int count = 0;
    dNode* currentNode = (dNode*)array->head;
    while (count <= index) {
        currentNode = currentNode->next;
        count++;
    }
    return currentNode;
}
cNode* getNode_c( Array* array, int index ) {
    int count = 0;
    cNode* currentNode = (cNode*)array->head;
    while (count <= index) {
        currentNode = currentNode->next;
        count++;
    }
    return currentNode;
}


int setValue_i( Array* array, int element, int index ) {
    iNode* currentNode = getNode_i(array, index);
    if (currentNode == NULL) return 1;
    currentNode->data = element;
    return 0;
}
int setValue_d( Array* array, double element, int index ) {
    dNode* currentNode = getNode_d(array, index);
    if (currentNode == NULL) return 1;
    currentNode->data = element;
    return 0;
}
int setValue_c( Array* array, char element, int index ) {
    cNode* currentNode = getNode_c(array, index);
    if (currentNode == NULL) return 1;
    currentNode->data = element;
    return 0;
}
