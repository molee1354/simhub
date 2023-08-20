#include <stdlib.h>
#include "array.h"

void append( Array* list, Token token ) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->token = token;
    newNode->next = NULL;

    ((Node*)list->tail)->next = newNode;
    ((Node*)list->tail)->token = token;
    list->tail = newNode;
}
