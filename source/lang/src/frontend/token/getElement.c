#include "array.h"

Token getElement( Array* array, int index ) {
    int count = 0;
    Node* currentNode = (Node*)array->head;
    while (count <= index) {
        currentNode = currentNode->next;
        count++;
    }
    return currentNode->token;
}   
