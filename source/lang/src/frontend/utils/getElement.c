#include "array.h"

Token getElement_T( Array* array, int index ) {
    int count = 0;
    Node* currentNode = (Node*)array->head;
    while (count <= index) {
        currentNode = currentNode->next;
        count++;
    }
    return currentNode->token;
}   
Statement getElement_S( Array* array, int index ) {
    int count = 0;
    sNode* currentNode = (sNode*)array->head;
    while (count <= index) {
        currentNode = currentNode->next;
        count++;
    }
    return currentNode->stmt;
}   
