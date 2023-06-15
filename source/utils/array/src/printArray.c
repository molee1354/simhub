#include <stdio.h>
#include "array.h"
#include "guard.h"

void printArray_i( Array* array ) {
    iNode* currentNode = ((iNode*)array->head)->next;
    printf("[");
    if (currentNode == array->tail) {
        puts("]");
        return;
    }
    while (currentNode->next->next != NULL) {
        printf("%d, ",currentNode->data);
        currentNode = currentNode->next;
    }
    printf("%d]\n", currentNode->data);
}
void printArray_d( Array* array ) {
    dNode* currentNode = ((dNode*)array->head)->next;
    printf("[");
    if (currentNode == array->tail) {
        puts("]");
        return;
    }
    while (currentNode->next->next != NULL) {
        printf("%.2f, ",currentNode->data);
        currentNode = currentNode->next;
    }
    printf("%.2f]\n", currentNode->data);
}
void printArray_c( Array* array ) {
    cNode* currentNode = ((cNode*)array->head)->next;
    printf("[");
    if (currentNode == array->tail) {
        puts("]");
        return;
    }
    while (currentNode->next->next != NULL) {
        printf("%c, ",currentNode->data);
        currentNode = currentNode->next;
    }
    printf("%c]\n", currentNode->data);
}
void printArray( Array* array ) {
    if (array->dtype == sizeof(int))    printArray_i(array);
    if (array->dtype == sizeof(double)) printArray_d(array);
    if (array->dtype == sizeof(char))   printArray_c(array);
}
