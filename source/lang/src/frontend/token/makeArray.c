#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "array.h"

Array* makeArray() {
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

    return array;
}

