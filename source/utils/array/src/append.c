#include <stdlib.h>
#include "array.h"
#include "guard.h"

void append_i( Array* list, int num ) {
    iNode* newNode = (iNode*)malloc(sizeof(iNode));
    newNode->data = -1.;
    newNode->next = NULL;

    ((iNode*)list->tail)->next = newNode;
    ((iNode*)list->tail)->data = num;
    list->tail = newNode;
}
void append_d( Array* list, double num ) {
    dNode* newNode = (dNode*)malloc(sizeof(dNode));
    newNode->data = -1.;
    newNode->next = NULL;

    ((dNode*)list->tail)->next = newNode;
    ((dNode*)list->tail)->data = num;
    list->tail = newNode;
}
void append_c( Array* list, char num ) {
    cNode* newNode = (cNode*)malloc(sizeof(cNode));
    newNode->data = '\0';
    newNode->next = NULL;

    ((cNode*)list->tail)->next = newNode;
    ((cNode*)list->tail)->data = num;
    list->tail = newNode;
}
