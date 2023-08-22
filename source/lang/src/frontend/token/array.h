#ifndef _array_h
#define _array_h

#include <stddef.h>
#include "token.h"

/*
 * Structs defined in the "guard.h" file to keep opacity
 * Nodes defined for different types.
 */
typedef struct TokenNode { 
    Token token;
    struct TokenNode* next;
} Node;


/*
 * TODO arrays could hold this struct instead
 */

/*
typedef enum {
    TokenElement,
    PrgmElement
} ElemType;
typedef struct ArrayElement {
    ElemType type;
    void* elem;
} Elem;*/


/*
 * Array object is a linked list
 */
typedef struct LinkedList {
    void* head;
    void* tail;
} Array;

/*
 * creates an array of type Token
 *  -> cast the head and tail nodes to the right datatype node
 */
Array* makeArray(void);

/*
 * Safely(!) getting rid of the array.
 */
int freeArray( Array* array );

/*
 * Adding a value to the beginning of an array
 */
void prepend( Array* array, Token token);

/*
 * Adding a value to the end of the array
 */
void append( Array* array, Token token);

/*
 * Deleting the respective node in the array. 
 * Could also be aliased to other functions
 */
void deleteHead( Array* array );
void deleteTail( Array* array );

/*
 * Getting the length of an array
 */
int getLength( Array* array );

/*
 * Getting a token element from an array at index
 */
Token getElement( Array* array, int index );

/*
 * Array printing.
 *  listRepr --> prints the linkedlist representation of the array
 *  printArray --> prints the array in square brackets
 */
void printArray( Array* array );

#endif
