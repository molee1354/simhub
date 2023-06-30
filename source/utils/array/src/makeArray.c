#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "array.h"
#include "_array.h"

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

