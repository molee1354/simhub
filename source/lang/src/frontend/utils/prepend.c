#include <stdlib.h>
#include "array.h"

void prepend_T( Array* list, Token elem ) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->token = elem;
    newNode->next = ((Node*)list->head)->next;
    ((Node*)list->head)->next = newNode;
}
void prepend_S( Array* list, Statement elem ) {
    sNode* newNode = (sNode*)malloc(sizeof(sNode));

    newNode->stmt = elem;
    newNode->next = ((sNode*)list->head)->next;
    ((sNode*)list->head)->next = newNode;
}
