#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "array.h"

Array* makeArray( ArrayType arrayType ) {
    if (arrayType == TokenArray) {
        Array* array = (Array*)malloc(sizeof(Array));

        Node* headNode = (Node*)malloc(sizeof(Node));
        Node* tailNode = (Node*)malloc(sizeof(Node));

        // create NULL head and tail tokens with End type
        Token headToken, tailToken;
        headToken.value = NULL;
        headToken.type = End;
        tailToken.value = NULL;
        tailToken.type = End;

        headNode->token = headToken;
        tailNode->token = tailToken;

        headNode->next = tailNode;
        tailNode->next = NULL;

        array->head = headNode;
        array->tail = tailNode;
        array->type = arrayType;

        return array;
    } else {
        Array* array = (Array*)malloc(sizeof(Array));

        sNode* headNode = (sNode*)malloc(sizeof(sNode));
        sNode* tailNode = (sNode*)malloc(sizeof(sNode));

        // create NULL head and tail tokens with End type
        Statement headToken, tailToken;
        headToken.kind = LL_EMPTY;
        tailToken.kind = LL_EMPTY;

        headNode->next = tailNode;
        tailNode->next = NULL;

        array->head = headNode;
        array->tail = tailNode;
        array->type = arrayType;

        return array;
    }
    return NULL;
}

