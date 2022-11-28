#ifndef _linkedlist_h
#define _linkedlist_h

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct LinkedList {
    struct Node* head;
    struct Node* tail;
} List;

List* makeList();

void prepend( List* list, int num );
void append( List* list, int num );

void deleteHead( List* list );
void deleteTail( List* list );

int getLength( List* list );
int getElement( List* list, int index );
int findIndex( List* list, int num );

void listRepr( List* list );
void printList( List* list );

#endif