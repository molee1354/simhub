#ifndef _array_h
#define _array_h

#include <stddef.h>
#include "../types.h"


/**
 * creates an array of type Token
 *  -> cast the head and tail nodes to the right datatype node
 */
Array* makeArray( ArrayType arrayType );

/*
 * Safely(!) getting rid of the array.
 */
int freeArray( Array* array );

/*
 * Adding a value to the beginning of an array
 */
void prepend_T( Array* array, Token elem );
void prepend_S( Array* array, Statement elem );
#define prepend(arr, elem) _Generic( (elem), \
                                Token: prepend_T, \
                            Statement: prepend_S)(arr, elem)

/*
 * Adding a value to the end of the array
 */
void append_T( Array* array, Token elem );
void append_S( Array* array, Statement elem );
#define append(arr, elem) _Generic( (elem), \
                                Token: append_T, \
                            Statement: append_S)(arr, elem)

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
Token getElement_T( Array* array, int index );
Statement getElement_S( Array* array, int index );

/*
 * Array printing.
 *  listRepr --> prints the linkedlist representation of the array
 *  printArray --> prints the array in square brackets
 */
void printArray( Array* array );

#endif
