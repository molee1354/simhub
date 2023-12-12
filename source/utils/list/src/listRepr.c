#include "list_commonincl.h"

int listRepr_i( List* list ) {
    iNode* currentNode = ((iNode*)list->head)->next;
    printf("Head->");
    if (currentNode == list->tail) {
        puts("Tail");
        return 0;
    }
    while (currentNode->next != NULL) {
        printf("%d->",currentNode->data);
        currentNode = currentNode->next;
    }
    puts("Tail");
    return 0;
}
int listRepr_d( List* list ) {
    dNode* currentNode = ((dNode*)list->head)->next;
    printf("Head->");
    if (currentNode == list->tail) {
        puts("Tail");
        return 0;
    }
    while (currentNode->next != NULL) {
        printf("%.2f->",currentNode->data);
        currentNode = currentNode->next;
    }
    puts("Tail");
    return 0;
}
int listRepr_c( List* list ) {
    cNode* currentNode = ((cNode*)list->head)->next;
    printf("Head->");
    if (currentNode == list->tail) {
        puts("Tail");
        return 0;
    }
    while (currentNode->next != NULL) {
        printf("%c->",currentNode->data);
        currentNode = currentNode->next;
    }
    puts("Tail");
    return 0;
}
int listRepr( List* list ) {
    if (list->dtype == sizeof(int))    return listRepr_i(list);
    if (list->dtype == sizeof(double)) return listRepr_d(list);
    if (list->dtype == sizeof(char))   return listRepr_c(list);
    return 1;
}
