#include <stdlib.h>
#include "array.h"

void prepend( Array* list, Token token ) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->token = token;
    newNode->next = ((Node*)list->head)->next;
    ((Node*)list->head)->next = newNode;
}
