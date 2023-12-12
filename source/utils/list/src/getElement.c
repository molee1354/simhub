#include "list_commonincl.h"

int getElement_i( List* list, int index ) {
    int count = 0;
    iNode* currentNode = (iNode*)list->head;
    while (count <= index) {
        currentNode = currentNode->next;
        count++;
    }
    return currentNode->data;
}   
double getElement_d( List* list, int index ) {
    int count = 0;
    dNode* currentNode = (dNode*)list->head;
    while (count <= index) {
        currentNode = currentNode->next;
        count++;
    }
    return currentNode->data;
}   
char getElement_c( List* list, int index ) {
    int count = 0;
    cNode* currentNode = (cNode*)list->head;
    while (count <= index) {
        currentNode = currentNode->next;
        count++;
    }
    return currentNode->data;
}   
