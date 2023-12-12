#ifndef _list_h
#define _list_h

#include <stddef.h>

/*
 * Structs defined in the "guard.h" file to keep opacity
 * Nodes defined for different types.
 */
typedef struct IntNode     iNode;
typedef struct DoubleNode  dNode;
typedef struct CharNode    cNode;

/*
 * List object is a linked list
 */
typedef struct LinkedList  List;

/*
 * creates an list of dtype
 *  -> cast the head annd tail nodes to the right datatype node
 */
List* makeList( size_t dtype );

/*
 * create a zero list of a certain size and of certain type
 *
 */
List* initList( size_t dtype, int size );

/*
 * create a ones list of a certain size and of certain type
 *
 */
List* onesList( size_t dtype, int size );

/*
 * converts a normal C list into an list object of the
 * same size
 */
List* toList_i( int* nList, int size );
List* toList_d( double* nList, int size );
List* toList_c( char* nList, int size );
#define toList(arr, elem) _Generic( (arr), \
                                int*: toList_i, \
                               char*: toList_c, \
                             double*: toList_d )(arr, elem)

/*
 * Safely(!) getting rid of the list.
 */
int freeList_i( List* list );
int freeList_d( List* list );
int freeList_c( List* list );
int freeList( List* list );

/*
 * Adding a value to the beginning of an list
 */
void prepend_i( List* list, int num );
void prepend_d( List* list, double num );
void prepend_c( List* list, char num );
#define prepend(arr, elem) _Generic( (elem), \
                                int: prepend_i, \
                               char: prepend_c, \
                             double: prepend_d )(arr, elem)

/*
 * Adding a value to the end of the list
 */
void append_i( List* list, int num );
void append_d( List* list, double num );
void append_c( List* list, char num );
#define append(arr, elem) _Generic( (elem), \
                                int: append_i, \
                               char: append_c, \
                             double: append_d )(arr, elem)

/*
 * Getting an element from a given index
 *     -> no multiple dispatch since the return types are different
 */
int    getElement_i( List* list, int index );
double getElement_d( List* list, int index );
char   getElement_c( List* list, int index );

/*
 * Setting an element at the given index as a given value
 */
int setValue_i( List* list, int element, int index );
int setValue_d( List* list, double element, int index );
int setValue_c( List* list, char element, int index );
#define setValue(arr, elem, idx) _Generic( (elem), \
                                int: setValue_i,   \
                               char: setValue_c,   \
                             double: setValue_d )(arr, elem, idx)


/*
 * Finding an index from a given element
 */
int getIndex_i( List* list, int num );
int getIndex_d( List* list, double num );
int getIndex_c( List* list, char num );
#define getIndex(arr, i) _Generic( (i), \
                                int: getIndex_i, \
                               char: getIndex_c, \
                             double: getIndex_d )(arr, i)

/*
 * Deleting the respective node in the list. 
 * Could also be aliased to other functions
 */
void deleteHead_i( List* list );
void deleteHead_d( List* list );
void deleteHead_c( List* list );
void deleteHead( List* list );

void deleteTail_i( List* list );
void deleteTail_d( List* list );
void deleteTail_c( List* list );
void deleteTail( List* list );

/*
 * Getting the length of an list
 */
int getLength_i( List* list );
int getLength_d( List* list );
int getLength_c( List* list );
int getLength( List* list );

/*
 * List printing.
 *  listRepr --> prints the linkedlist representation of the list
 *  printList --> prints the list in square brackets
 */
void printList_i( List* list );
void printList_d( List* list );
void printList_c( List* list );
void printList( List* list );

/*
 * listRepr() type writers return int to check for errors
 */
int listRepr_i( List* list );
int listRepr_d( List* list );
int listRepr_c( List* list );
int listRepr( List* list );

#endif
