#include "list_commonincl.h"

void deleteHead_i( List* list ) {
    iNode* temp = ((iNode*)list->head)->next;
    ((iNode*)list->head)->next = temp->next;
    free(temp);
    temp = NULL;
}
void deleteHead_d( List* list ) {
    dNode* temp = ((dNode*)list->head)->next;
    ((dNode*)list->head)->next = temp->next;
    free(temp);
    temp = NULL;
}
void deleteHead_c( List* list ) {
    cNode* temp = ((cNode*)list->head)->next;
    ((cNode*)list->head)->next = temp->next;
    free(temp);
    temp = NULL;
}
void deleteHead( List* list ){
    if (list->dtype == sizeof(int))    deleteHead_i(list);
    if (list->dtype == sizeof(double)) deleteHead_d(list);
    if (list->dtype == sizeof(char))   deleteHead_c(list);
}
