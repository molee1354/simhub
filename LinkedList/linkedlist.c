// singly linked list implementation

#include<stdio.h>
#include<stdlib.h>
#include "linkedlist.h"

List* makeList() {
    List* linkedlist = (List*)malloc(sizeof(List));
    Node* headNode = (Node*)malloc(sizeof(Node));
    Node* tailNode = (Node*)malloc(sizeof(Node));

    headNode->data = -1;
    tailNode->data = -1;

    headNode->next = tailNode;
    tailNode->next = NULL;

    linkedlist->head = headNode;
    linkedlist->tail = tailNode;

    return linkedlist;
}

void prepend( List* list, int num ) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = num;
    newNode->next = list->head->next;

    list->head->next = newNode;
}

void append( List* list, int num ) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = -1;
    newNode->next = NULL;

    list->tail->next = newNode;
    list->tail->data = num;
    list->tail = newNode;
}

void deleteHead( List* list ) {
    list->head->next = list->head->next->next;
}

void deleteTail( List* list ) {
    Node* currentNode = list->head->next;

    while (currentNode->next != NULL) {
        if (currentNode->next->next == NULL) {
            currentNode->next = NULL;
            return;
        }
        currentNode = currentNode->next;
    }
}

int getLength( List* list ) {
    int length = 0;
    Node* currentNode = list->head->next;

    while (currentNode->next != NULL) {
        length++;
    }
    return length;
}

int getElement( List* list, int index ) {
    int count = 0;
    Node* currentNode = list->head->next;

    while (count < index) {
        currentNode = currentNode->next;
        count++;
    }

    return currentNode->data;
}

int findIndex( List* list, int num ) {
    int idx = 0;
    Node* currentNode = list->head->next;

    do {
        if (currentNode->data == num) {
            return idx;
        }
        currentNode = currentNode->next;
        idx++;
    } while (currentNode->data != num || currentNode->next != NULL);

    return list->tail->data;
}

void listRepr( List* list ) {
    Node* currentNode = list->head->next;

    printf("Head -> ");
    while (currentNode->next != NULL) {
        printf("%d -> ",currentNode->data);
        currentNode = currentNode->next;
    }
    puts("Tail");
}

void printList( List* list ) {
    Node* currentNode = list->head->next;

    printf("[");
    while (currentNode->next->next != NULL) {
        printf("%d, ",currentNode->data);
        currentNode = currentNode->next;
    }
    printf("%d]\n", currentNode->data);
}