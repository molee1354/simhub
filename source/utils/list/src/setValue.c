#include "list_commonincl.h"

iNode* getNode_i( List* list, int index ) {
    int count = 0;
    iNode* currentNode = (iNode*)list->head;
    while (count <= index) {
        currentNode = currentNode->next;
        count++;
    }
    return currentNode;
}
dNode* getNode_d( List* list, int index ) {
    int count = 0;
    dNode* currentNode = (dNode*)list->head;
    while (count <= index) {
        currentNode = currentNode->next;
        count++;
    }
    return currentNode;
}
cNode* getNode_c( List* list, int index ) {
    int count = 0;
    cNode* currentNode = (cNode*)list->head;
    while (count <= index) {
        currentNode = currentNode->next;
        count++;
    }
    return currentNode;
}


int setValue_i( List* list, int element, int index ) {
    iNode* currentNode = getNode_i(list, index);
    if (currentNode == NULL) return 1;
    currentNode->data = element;
    return 0;
}
int setValue_d( List* list, double element, int index ) {
    dNode* currentNode = getNode_d(list, index);
    if (currentNode == NULL) return 1;
    currentNode->data = element;
    return 0;
}
int setValue_c( List* list, char element, int index ) {
    cNode* currentNode = getNode_c(list, index);
    if (currentNode == NULL) return 1;
    currentNode->data = element;
    return 0;
}
