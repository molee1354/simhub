#include <stdio.h>
#include <stdlib.h>

#include "array.h"

#ifndef _test_h
#define _test_h

#define TYPE int

#define TEST_FAIL(reason)      printf("\t=> [  \033[0;33mFAIL\033[0m  ] --> %s\n\n", reason); \
                               testFail++

#define TEST_SUCCESS()         printf("\t=> [  \033[0;32mPASS\033[0m  ]\n\n"); \
                               testSuccess++

/*
 * Testing the makeArray() function
 */
int TEST_makeArray_i(void);
int TEST_makeArray_d(void);
int TEST_makeArray_c(void);
#define TEST_makeArray(x) _Generic( (x), \
                                int: TEST_makeArray_i, \
                               char: TEST_makeArray_c, \
                             double: TEST_makeArray_d )()

/*
 * Testing the toArray() function
 */
int TEST_toArray_i(void);
int TEST_toArray_d(void);
int TEST_toArray_c(void);
#define TEST_toArray(x) _Generic( (x), \
                                int: TEST_toArray_i, \
                               char: TEST_toArray_c, \
                             double: TEST_toArray_d )()

/*
 * Testing the freeArray() function
 */
int TEST_freeArray_i( Array* array, int num );
int TEST_freeArray_d( Array* array, double num );
int TEST_freeArray_c( Array* array, char num );
#define TEST_freeArray(arr, elem) _Generic( (elem), \
                                int: TEST_freeArray_i, \
                               char: TEST_freeArray_c, \
                             double: TEST_freeArray_d )(arr, elem)

/*
 * Testing the append() function
 */
int TEST_append_i( Array* array, int num );
int TEST_append_d( Array* array, double num );
int TEST_append_c( Array* array, char num );
#define TEST_append(arr, elem) _Generic( (elem), \
                                int: TEST_append_i, \
                               char: TEST_append_c, \
                             double: TEST_append_d )(arr, elem)

/*
 * Testing the prepend() function
 */
int TEST_prepend_i( Array* array, int num );
int TEST_prepend_d( Array* array, double num );
int TEST_prepend_c( Array* array, char num );
#define TEST_prepend(arr, elem) _Generic( (elem), \
                                int: TEST_prepend_i, \
                               char: TEST_prepend_c, \
                             double: TEST_prepend_d )(arr, elem)

/*
 * Testing the deleteHead() function
 */
int TEST_deleteHead_i( Array* array, int dtype );
int TEST_deleteHead_d( Array* array, double dtype );
int TEST_deleteHead_c( Array* array, char dtype );
#define TEST_deleteHead(arr, elem) _Generic( (elem), \
                                int: TEST_deleteHead_i, \
                               char: TEST_deleteHead_c, \
                             double: TEST_deleteHead_d )(arr, elem)

/*
 * Testing the deleteTail() function
 */
int TEST_deleteTail_i( Array* array, int dtype );
int TEST_deleteTail_d( Array* array, double dtype );
int TEST_deleteTail_c( Array* array, char dtype );
#define TEST_deleteTail(arr, elem) _Generic( (elem), \
                                int: TEST_deleteTail_i, \
                               char: TEST_deleteTail_c, \
                             double: TEST_deleteTail_d )(arr, elem)

/*
 * Testing the getIndex() function
 */
int TEST_getIndex_i( Array* array, int num );
int TEST_getIndex_d( Array* array, double num );
int TEST_getIndex_c( Array* array, char num );
#define TEST_getIndex(arr, elem) _Generic( (elem), \
                                int: TEST_getIndex_i, \
                               char: TEST_getIndex_c, \
                             double: TEST_getIndex_d )(arr, elem)

/*
 * Testing the getElement() function
 */
int TEST_getElement_i( Array* array, int index, int dtype );
int TEST_getElement_d( Array* array, int index, double dtype );
int TEST_getElement_c( Array* array, int index, char dtype );
#define TEST_getElement(arr, idx, elem) _Generic( (elem), \
                                int: TEST_getElement_i, \
                               char: TEST_getElement_c, \
                             double: TEST_getElement_d )(arr, idx, elem)

/*
 * Testing the getLength() function
 */
int TEST_getLength_i( Array* array, int dtype );
int TEST_getLength_d( Array* array, double dtype );
int TEST_getLength_c( Array* array, char dtype );
#define TEST_getLength(arr, dtype) _Generic( (dtype), \
                                int: TEST_getLength_i, \
                               char: TEST_getLength_c, \
                             double: TEST_getLength_d )(arr, dtype)

/*
 * Testing the listRepr() function
 */
int TEST_listRepr_i( Array* array, int dtype );
int TEST_listRepr_d( Array* array, double dtype );
int TEST_listRepr_c( Array* array, char dtype );
#define TEST_listRepr(arr, elem) _Generic( (elem), \
                                int: TEST_listRepr_i, \
                               char: TEST_listRepr_c, \
                             double: TEST_listRepr_d )(arr, elem)

/*
 * Testing the printArray() function
 */
int TEST_printArray_i( Array* array, int dtype );
int TEST_printArray_d( Array* array, double dtype );
int TEST_printArray_c( Array* array, char dtype );
#define TEST_printArray(arr, elem) _Generic( (elem), \
                                int: TEST_printArray_i, \
                               char: TEST_printArray_c, \
                             double: TEST_printArray_d )(arr, elem)

/*
 * Function to create test arrays
 */
Array* makeTestArray_i(); 
Array* makeTestArray_d();
Array* makeTestArray_c(); 
#define makeTestArray(elem) _Generic( (elem), \
                                int: makeTestArray_i, \
                               char: makeTestArray_c, \
                             double: makeTestArray_d )()

#endif
