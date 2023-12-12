#include "list_commonincl.h"

void printList_i( List* list ) {
    iNode* currentNode = ((iNode*)list->head)->next;
    printf("[");
    if (currentNode == list->tail) {
        puts("]");
        return;
    }
    while (currentNode->next->next != NULL) {
        printf("%d, ",currentNode->data);
        currentNode = currentNode->next;
    }
    printf("%d]\n", currentNode->data);
}
void printList_d( List* list ) {
    dNode* currentNode = ((dNode*)list->head)->next;
    printf("[");
    if (currentNode == list->tail) {
        puts("]");
        return;
    }
    while (currentNode->next->next != NULL) {
        printf("%.2f, ",currentNode->data);
        currentNode = currentNode->next;
    }
    printf("%.2f]\n", currentNode->data);
}
void printList_c( List* list ) {
    cNode* currentNode = ((cNode*)list->head)->next;
    printf("[");
    if (currentNode == list->tail) {
        puts("]");
        return;
    }
    while (currentNode->next->next != NULL) {
        printf("%c, ",currentNode->data);
        currentNode = currentNode->next;
    }
    printf("%c]\n", currentNode->data);
}
void printList( List* list ) {
    if (list->dtype == sizeof(int))    printList_i(list);
    if (list->dtype == sizeof(double)) printList_d(list);
    if (list->dtype == sizeof(char))   printList_c(list);
}
