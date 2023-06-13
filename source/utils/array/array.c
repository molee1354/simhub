// singly linked list implementation

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "array.h"


Array* makeArray(size_t dtype) {
    Array* array = (Array*)malloc(sizeof(Array));
    array->dtype = dtype;

    if (dtype == sizeof(int)) {
        iNode* headNode = (iNode*)malloc(sizeof(iNode));
        iNode* tailNode = (iNode*)malloc(sizeof(iNode));

        headNode->data = -1;
        tailNode->data = -1;

        headNode->next = tailNode;
        tailNode->next = NULL;

        array->head = headNode;
        array->tail = tailNode;

    } else if (dtype == sizeof(double)) {
        dNode* headNode = (dNode*)malloc(sizeof(dNode));
        dNode* tailNode = (dNode*)malloc(sizeof(dNode));

        headNode->data = -1.;
        tailNode->data = -1.;

        headNode->next = tailNode;
        tailNode->next = NULL;

        array->head = headNode;
        array->tail = tailNode;

    } else if (dtype == sizeof(char)) {
        cNode* headNode = (cNode*)malloc(sizeof(cNode));
        cNode* tailNode = (cNode*)malloc(sizeof(cNode));

        headNode->data = '\0';
        tailNode->data = '\0';

        headNode->next = tailNode;
        tailNode->next = NULL;

        array->head = headNode;
        array->tail = tailNode;
    } else {
        printf("Unsupported datatype taken as argument in \
                \"makeList( size_t dtype )\". Defaulting to \
                \"int\" type\n");
        iNode* headNode = (iNode*)malloc(sizeof(iNode));
        iNode* tailNode = (iNode*)malloc(sizeof(iNode));

        headNode->data = -1;
        tailNode->data = -1;

        headNode->next = tailNode;
        tailNode->next = NULL;

        array->head = headNode;
        array->tail = tailNode;
    }

    return array;
}

void prepend_i( Array* list, int num ) {
    iNode* newNode = (iNode*)malloc(sizeof(iNode));

    newNode->data = num;
    newNode->next = ((iNode*)list->head)->next;
    ((iNode*)list->head)->next = newNode;
}
void prepend_d( Array* list, double num ) {
    dNode* newNode = (dNode*)malloc(sizeof(dNode));

    newNode->data = num;
    newNode->next = ((dNode*)list->head)->next;
    ((dNode*)list->head)->next = newNode;
}
void prepend_c( Array* list, char num ) {
    cNode* newNode = (cNode*)malloc(sizeof(cNode));

    newNode->data = num;
    newNode->next = ((cNode*)list->head)->next;
    ((cNode*)list->head)->next = newNode;
}

void append_i( Array* list, int num ) {
    iNode* newNode = (iNode*)malloc(sizeof(iNode));
    newNode->data = -1.;
    newNode->next = NULL;

    ((iNode*)list->tail)->next = newNode;
    ((iNode*)list->tail)->data = num;
    list->tail = newNode;
}
void append_d( Array* list, double num ) {
    dNode* newNode = (dNode*)malloc(sizeof(dNode));
    newNode->data = -1.;
    newNode->next = NULL;

    ((dNode*)list->tail)->next = newNode;
    ((dNode*)list->tail)->data = num;
    list->tail = newNode;
}
void append_c( Array* list, char num ) {
    cNode* newNode = (cNode*)malloc(sizeof(cNode));
    newNode->data = '\0';
    newNode->next = NULL;

    ((cNode*)list->tail)->next = newNode;
    ((cNode*)list->tail)->data = num;
    list->tail = newNode;
}

int getElement_i( Array* array, int index ) {
    int count = 0;
    iNode* currentNode = (iNode*)array->head;
    while (count <= index) {
        currentNode = currentNode->next;
        count++;
    }
    return currentNode->data;
}   
double getElement_d( Array* array, int index ) {
    int count = 0;
    dNode* currentNode = (dNode*)array->head;
    while (count <= index) {
        currentNode = currentNode->next;
        count++;
    }
    return currentNode->data;
}   
char getElement_c( Array* array, int index ) {
    int count = 0;
    cNode* currentNode = (cNode*)array->head;
    while (count <= index) {
        currentNode = currentNode->next;
        count++;
    }
    return currentNode->data;
}   

int getIndex_i( Array* array, int num ) {
    iNode* currentNode = ((iNode*)array->head)->next;
    int idx = 0;
    while (currentNode->data != num || currentNode->next != NULL) {
        if (currentNode->data == num) return idx;
        currentNode = currentNode->next;
        idx++;
    }
    return getLength(array)-1;
}
int getIndex_d( Array* array, double num ) {
    dNode* currentNode = ((dNode*)array->head)->next;
    int idx = 0;
    while (currentNode->data != num || currentNode->next != NULL) {
        if (currentNode->data == num) return idx;
        currentNode = currentNode->next;
        idx++;
    }
    return getLength(array)-1;
}
int getIndex_c( Array* array, char num ) {
    cNode* currentNode = ((cNode*)array->head)->next;
    int idx = 0;
    while (currentNode->data != num || currentNode->next != NULL) {
        if (currentNode->data == num) return idx;
        currentNode = currentNode->next;
        idx++;
    }
    return getLength(array)-1;
}

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

void deleteTail_i(Array* array) {
    iNode* currentNode = ((iNode*)array->head)->next;
    while (currentNode->next->next != NULL) {
        currentNode = currentNode->next;
    }
    free(currentNode->next);
    currentNode->next = NULL;
    array->tail = currentNode;
}
void deleteTail_d(Array* array) {
    dNode* currentNode = ((dNode*)array->head)->next;
    while (currentNode->next->next != NULL) {
        currentNode = currentNode->next;
    }
    free(currentNode->next);
    currentNode->next = NULL;
    array->tail = currentNode;
}
void deleteTail_c(Array* array) {
    cNode* currentNode = ((cNode*)array->head)->next;
    while (currentNode->next->next != NULL) {
        currentNode = currentNode->next;
    }
    free(currentNode->next);
    currentNode->next = NULL;
    array->tail = currentNode;
}
void deleteTail( Array* array ){
    if (array->dtype == sizeof(int))    deleteTail_i(array);
    if (array->dtype == sizeof(double)) deleteTail_d(array);
    if (array->dtype == sizeof(char))   deleteTail_c(array);
}

int freeArray_i( Array* array ) {
    while ( ((iNode*)array->head)->next->next != NULL ) {
        deleteHead_i(array);
        continue;
    }
    free(array->head);
    array->head = NULL;
    free(array->tail);
    array->tail = NULL;
    free(array);
    array = NULL;
    return 0;
}
int freeArray_d( Array* array ) {
    while ( ((dNode*)array->head)->next != array->tail) {
        deleteHead_d(array);
        continue;
    }
    free(array->head);
    array->head = NULL;
    free(array->tail);
    array->tail = NULL;
    free(array);
    array = NULL;
    return 0;
}
int freeArray_c( Array* array ) {
    while ( ((cNode*)array->head)->next != array->tail) {
        deleteHead_c(array);
        continue;
    }
    free(array->head);
    array->head = NULL;
    free(array->tail);
    array->tail = NULL;
    free(array);
    array = NULL;
    return 0;
}
int freeArray( Array* array ){
    if (array->dtype == sizeof(int))    freeArray_i(array);
    if (array->dtype == sizeof(double)) freeArray_d(array);
    if (array->dtype == sizeof(char))   freeArray_c(array);
}

int getLength_i( Array* array ) {
    int length = 1;
    iNode* currentNode = ((iNode*)array->head)->next;
    if (currentNode == array->tail) return 0;
    while (currentNode->next->next != NULL) {
        length++;
        currentNode = currentNode->next;
    }
    return length;
}
int getLength_d( Array* array ) {
    int length = 1;
    dNode* currentNode = ((dNode*)array->head)->next;
    if (currentNode == array->tail) return 0;
    while (currentNode->next->next != NULL) {
        length++;
        currentNode = currentNode->next;
    }
    return length;
}
int getLength_c( Array* array ) {
    int length = 1;
    cNode* currentNode = ((cNode*)array->head)->next;
    if (currentNode == array->tail) return 0;
    while (currentNode->next->next != NULL) {
        length++;
        currentNode = currentNode->next;
    }
    return length;
}
int getLength( Array* array ){
    if (array->dtype == sizeof(int))    return getLength_i(array);
    if (array->dtype == sizeof(double)) return getLength_d(array);
    if (array->dtype == sizeof(char))   return getLength_c(array);
}

void listRepr_i( Array* array ) {
    iNode* currentNode = ((iNode*)array->head)->next;
    printf("Head->");
    if (currentNode == array->tail) {
        puts("Tail");
        return;
    }
    while (currentNode->next != NULL) {
        printf("%d->",currentNode->data);
        currentNode = currentNode->next;
    }
    puts("Tail");
}
void listRepr_d( Array* array ) {
    dNode* currentNode = ((dNode*)array->head)->next;
    printf("Head->");
    if (currentNode == array->tail) {
        puts("Tail");
        return;
    }
    while (currentNode->next != NULL) {
        printf("%f->",currentNode->data);
        currentNode = currentNode->next;
    }
    puts("Tail");
}
void listRepr_c( Array* array ) {
    cNode* currentNode = ((cNode*)array->head)->next;
    printf("Head->");
    if (currentNode == array->tail) {
        puts("Tail");
        return;
    }
    while (currentNode->next != NULL) {
        printf("%c->",currentNode->data);
        currentNode = currentNode->next;
    }
    puts("Tail");
}
void listRepr( Array* array ) {
    if (array->dtype == sizeof(int))    listRepr_i(array);
    if (array->dtype == sizeof(double)) listRepr_d(array);
    if (array->dtype == sizeof(char))   listRepr_c(array);
}

void printArray_i( Array* array ) {
    iNode* currentNode = ((iNode*)array->head)->next;
    printf("[");
    if (currentNode == array->tail) {
        puts("]");
        return;
    }
    while (currentNode->next->next != NULL) {
        printf("%d, ",currentNode->data);
        currentNode = currentNode->next;
    }
    printf("%d]\n", currentNode->data);
}
void printArray_d( Array* array ) {
    dNode* currentNode = ((dNode*)array->head)->next;
    printf("[");
    if (currentNode == array->tail) {
        puts("]");
        return;
    }
    while (currentNode->next->next != NULL) {
        printf("%f, ",currentNode->data);
        currentNode = currentNode->next;
    }
    printf("%f]\n", currentNode->data);
}
void printArray_c( Array* array ) {
    cNode* currentNode = ((cNode*)array->head)->next;
    printf("[");
    if (currentNode == array->tail) {
        puts("]");
        return;
    }
    while (currentNode->next->next != NULL) {
        printf("%c, ",currentNode->data);
        currentNode = currentNode->next;
    }
    printf("%c]\n", currentNode->data);
}
void printArray( Array* array ) {
    if (array->dtype == sizeof(int))    printArray_i(array);
    if (array->dtype == sizeof(double)) printArray_d(array);
    if (array->dtype == sizeof(char))   printArray_c(array);
}
