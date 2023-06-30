#include <stdlib.h>
#include "array.h"
#include "_array.h"

void deleteHead_i( Array* array ) {
    iNode* temp = ((iNode*)array->head)->next;
    ((iNode*)array->head)->next = temp->next;
    free(temp);
    temp = NULL;
}
void deleteHead_d( Array* array ) {
    dNode* temp = ((dNode*)array->head)->next;
    ((dNode*)array->head)->next = temp->next;
    free(temp);
    temp = NULL;
}
void deleteHead_c( Array* array ) {
    cNode* temp = ((cNode*)array->head)->next;
    ((cNode*)array->head)->next = temp->next;
    free(temp);
    temp = NULL;
}
void deleteHead( Array* array ){
    if (array->dtype == sizeof(int))    deleteHead_i(array);
    if (array->dtype == sizeof(double)) deleteHead_d(array);
    if (array->dtype == sizeof(char))   deleteHead_c(array);
}
