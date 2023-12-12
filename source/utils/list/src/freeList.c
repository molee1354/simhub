#include "list_commonincl.h"

int freeList_i( List* list ) {
    while ( ((iNode*)list->head)->next->next != NULL ) {
        deleteHead_i(list);
        continue;
    }
    free(list->head);
    list->head = NULL;
    free(list->tail);
    list->tail = NULL;
    free(list);
    list = NULL;
    return 0;
}
int freeList_d( List* list ) {
    while ( ((dNode*)list->head)->next != list->tail) {
        deleteHead_d(list);
        continue;
    }
    free(list->head);
    list->head = NULL;
    free(list->tail);
    list->tail = NULL;
    free(list);
    list = NULL;
    return 0;
}
int freeList_c( List* list ) {
    while ( ((cNode*)list->head)->next != list->tail) {
        deleteHead_c(list);
        continue;
    }
    free(list->head);
    list->head = NULL;
    free(list->tail);
    list->tail = NULL;
    free(list);
    list = NULL;
    return 0;
}
int freeList( List* list ){
    if (list->dtype == sizeof(int))    return freeList_i(list);
    if (list->dtype == sizeof(double)) return freeList_d(list);
    if (list->dtype == sizeof(char))   return freeList_c(list);
    return 1;
}
