#ifndef _array_h
#define _array_h

#include <stddef.h>

/*
 * Different node types based on datatype
 */
typedef struct iNode {    int data; struct iNode* next; } iNode;
typedef struct dNode { double data; struct dNode* next; } dNode;
typedef struct cNode {   char data; struct cNode* next; } cNode;

/*
 * struct to hold the array
 * the `head` and `tail` pointers will be cast to its types later.
 */
typedef struct LinkedList {
    void* head;
    void* tail;
    size_t dtype;
} Array;

/*
 * creates an array of dtype
 *  -> cast the head annd tail nodes to the right datatype node
 */
Array* makeArray( size_t dtype );

/*
 * Safely(!) getting rid of the array.
 */
void freeArray_i( Array* array );
void freeArray_d( Array* array );
void freeArray_c( Array* array );
void freeArray( Array* array );

/*
 * Adding a value to the beginning of an array
 */
void prepend_i( Array* array, int num );
void prepend_d( Array* array, double num );
void prepend_c( Array* array, char num );
#define prepend(arr, elem) _Generic( (elem), \
                                int: prepend_i, \
                               char: prepend_c, \
                             double: prepend_d )(arr, elem)

/*
 * Adding a value to the end of the array
 */
void append_i( Array* array, int num );
void append_d( Array* array, double num );
void append_c( Array* array, char num );
#define append(arr, elem) _Generic( (elem), \
                                int: append_i, \
                               char: append_c, \
                             double: append_d )(arr, elem)

/*
 * Getting an element from a given index
 */
int getElement_i( Array* array, int index );
double getElement_d( Array* array, int index );
char getElement_c( Array* array, int index );
#define getElement(arr, i) _Generic( (i), \
                                int: getElement_i, \
                               char: getElement_c, \
                             double: getElement_d )(arr, i)

/*
 * Finding an index from a given element
 */
int findIndex_i( Array* array, int num );
int findIndex_d( Array* array, double num );
int findIndex_c( Array* array, char num );
#define findIndex(arr, i) _Generic( (i), \
                                int: findIndex_i, \
                               char: findIndex_c, \
                             double: findIndex_d )(arr, i)

/*
 * Deleting the respective node in the array. 
 * Could also be aliased to other functions
 */
void deleteHead_i( Array* array );
void deleteHead_d( Array* array );
void deleteHead_c( Array* array );
void deleteHead( Array* array );

void deleteTail_i( Array* array );
void deleteTail_d( Array* array );
void deleteTail_c( Array* array );
void deleteTail( Array* array );

/*
 * Getting the length of an array
 */
int getLength_i( Array* array );
int getLength_d( Array* array );
int getLength_c( Array* array );
int getLength( Array* array );

/*
 * Array printing.
 *  listRepr --> prints the linkedlist representation of the array
 *  printArray --> prints the array in square brackets
 */
void printArray_i( Array* array );
void printArray_d( Array* array );
void printArray_c( Array* array );
void printArray( Array* array );

void listRepr_i( Array* array );
void listRepr_d( Array* array );
void listRepr_c( Array* array );
void listRepr( Array* array );

#endif
