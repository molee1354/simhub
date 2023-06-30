#include <stdio.h>
#include "array.h"
#include "_array.h"

int listRepr_i( Array* array ) {
    iNode* currentNode = ((iNode*)array->head)->next;
    printf("Head->");
    if (currentNode == array->tail) {
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
int listRepr_d( Array* array ) {
    dNode* currentNode = ((dNode*)array->head)->next;
    printf("Head->");
    if (currentNode == array->tail) {
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
int listRepr_c( Array* array ) {
    cNode* currentNode = ((cNode*)array->head)->next;
    printf("Head->");
    if (currentNode == array->tail) {
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
int listRepr( Array* array ) {
    if (array->dtype == sizeof(int))    return listRepr_i(array);
    if (array->dtype == sizeof(double)) return listRepr_d(array);
    if (array->dtype == sizeof(char))   return listRepr_c(array);
    return 1;
}
