#include "array.h"
#include "_array.h"

int getElement_i( Array* array, int index ) {
    int count = 0;
    iNode* currentNode = (iNode*)array->head;
    while (count <= index) {
        currentNode = currentNode->next;
        count++;
    }
    return currentNode->data;
}   
double getElement_d( Array* array, int index ) {
    int count = 0;
    dNode* currentNode = (dNode*)array->head;
    while (count <= index) {
        currentNode = currentNode->next;
        count++;
    }
    return currentNode->data;
}   
char getElement_c( Array* array, int index ) {
    int count = 0;
    cNode* currentNode = (cNode*)array->head;
    while (count <= index) {
        currentNode = currentNode->next;
        count++;
    }
    return currentNode->data;
}   
