#include <stdlib.h>
#include "array.h"
#include "guard.h"

void prepend_i( Array* list, int num ) {
    iNode* newNode = (iNode*)malloc(sizeof(iNode));

    newNode->data = num;
    newNode->next = ((iNode*)list->head)->next;
    ((iNode*)list->head)->next = newNode;
}
void prepend_d( Array* list, double num ) {
    dNode* newNode = (dNode*)malloc(sizeof(dNode));

    newNode->data = num;
    newNode->next = ((dNode*)list->head)->next;
    ((dNode*)list->head)->next = newNode;
}
void prepend_c( Array* list, char num ) {
    cNode* newNode = (cNode*)malloc(sizeof(cNode));

    newNode->data = num;
    newNode->next = ((cNode*)list->head)->next;
    ((cNode*)list->head)->next = newNode;
}
