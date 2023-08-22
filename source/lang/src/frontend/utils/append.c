#include <stdlib.h>
#include "array.h"

void append_T( Array* list, Token elem ) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->token = elem;
    newNode->next = NULL;

    ((Node*)list->tail)->next = newNode;
    ((Node*)list->tail)->token = elem;
    list->tail = newNode;
}
void append_S( Array* list, Statement elem ) {
    sNode* newNode = (sNode*)malloc(sizeof(sNode));
    newNode->stmt = elem;
    newNode->next = NULL;

    ((sNode*)list->tail)->next = newNode;
    ((sNode*)list->tail)->stmt = elem;
    list->tail = newNode;
}
