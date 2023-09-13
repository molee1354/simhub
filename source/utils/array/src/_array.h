#ifndef _guard_h
#define _guard_h

#ifdef NAME_MANGLE
#include "array_array.h"
#else
#include "array.h"
#endif

/*
 * Different node types based on datatype
 */
typedef struct IntNode    { int    data; struct IntNode*    next; } iNode;
typedef struct DoubleNode { double data; struct DoubleNode* next; } dNode;
typedef struct CharNode   { char   data; struct CharNode*   next; } cNode;

/*
 * struct to hold the array
 * the `head` and `tail` pointers will be cast to its types later.
 */
typedef struct LinkedList { void* head; void* tail; size_t dtype; } Array;

#endif

