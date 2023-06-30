#include "array.h"
#include "_array.h"

int getLength_i( Array* array ) {
    int length = 1;
    iNode* currentNode = ((iNode*)array->head)->next;
    if (currentNode == array->tail) return 0;
    while (currentNode->next->next != NULL) {
        length++;
        currentNode = currentNode->next;
    }
    return length;
}
int getLength_d( Array* array ) {
    int length = 1;
    dNode* currentNode = ((dNode*)array->head)->next;
    if (currentNode == array->tail) return 0;
    while (currentNode->next->next != NULL) {
        length++;
        currentNode = currentNode->next;
    }
    return length;
}
int getLength_c( Array* array ) {
    int length = 1;
    cNode* currentNode = ((cNode*)array->head)->next;
    if (currentNode == array->tail) return 0;
    while (currentNode->next->next != NULL) {
        length++;
        currentNode = currentNode->next;
    }
    return length;
}
int getLength( Array* array ){
    if (array->dtype == sizeof(int))    return getLength_i(array);
    if (array->dtype == sizeof(double)) return getLength_d(array);
    if (array->dtype == sizeof(char))   return getLength_c(array);
    return 1;
}
