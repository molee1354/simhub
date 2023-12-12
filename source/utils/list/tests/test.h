#include <stdio.h>
#include <stdlib.h>

// #include "../src/array.h"

#ifndef _test_h
#define _test_h

#include "array.h"

#define TYPE int

#define TEST_FAIL(reason)      printf("\t=> [  \033[0;33mFAIL\033[0m  ] --> %s\n\n", reason); \
                               testFail++

#define TEST_SUCCESS()         printf("\t=> [  \033[0;32mPASS\033[0m  ]\n\n"); \
                               testSuccess++

/*
 * Testing the makeList() function
 */
int TEST_makeList_i(void);
int TEST_makeList_d(void);
int TEST_makeList_c(void);
#define TEST_makeList(x) _Generic( (x), \
                                int: TEST_makeList_i, \
                               char: TEST_makeList_c, \
                             double: TEST_makeList_d )()

/*
 * Testing the toList() function
 */
int TEST_toList_i(void);
int TEST_toList_d(void);
int TEST_toList_c(void);
#define TEST_toList(x) _Generic( (x), \
                                int: TEST_toList_i, \
                               char: TEST_toList_c, \
                             double: TEST_toList_d )()

/*
 * Testing the freeList() function
 */
int TEST_freeList_i( List* array, int num );
int TEST_freeList_d( List* array, double num );
int TEST_freeList_c( List* array, char num );
#define TEST_freeList(arr, elem) _Generic( (elem), \
                                int: TEST_freeList_i, \
                               char: TEST_freeList_c, \
                             double: TEST_freeList_d )(arr, elem)

/*
 * Testing the append() function
 */
int TEST_append_i( List* array, int num );
int TEST_append_d( List* array, double num );
int TEST_append_c( List* array, char num );
#define TEST_append(arr, elem) _Generic( (elem), \
                                int: TEST_append_i, \
                               char: TEST_append_c, \
                             double: TEST_append_d )(arr, elem)

/*
 * Testing the prepend() function
 */
int TEST_prepend_i( List* array, int num );
int TEST_prepend_d( List* array, double num );
int TEST_prepend_c( List* array, char num );
#define TEST_prepend(arr, elem) _Generic( (elem), \
                                int: TEST_prepend_i, \
                               char: TEST_prepend_c, \
                             double: TEST_prepend_d )(arr, elem)

/*
 * Testing the deleteHead() function
 */
int TEST_deleteHead_i( List* array, int dtype );
int TEST_deleteHead_d( List* array, double dtype );
int TEST_deleteHead_c( List* array, char dtype );
#define TEST_deleteHead(arr, elem) _Generic( (elem), \
                                int: TEST_deleteHead_i, \
                               char: TEST_deleteHead_c, \
                             double: TEST_deleteHead_d )(arr, elem)

/*
 * Testing the deleteTail() function
 */
int TEST_deleteTail_i( List* array, int dtype );
int TEST_deleteTail_d( List* array, double dtype );
int TEST_deleteTail_c( List* array, char dtype );
#define TEST_deleteTail(arr, elem) _Generic( (elem), \
                                int: TEST_deleteTail_i, \
                               char: TEST_deleteTail_c, \
                             double: TEST_deleteTail_d )(arr, elem)

/*
 * Testing the getIndex() function
 */
int TEST_getIndex_i( List* array, int num );
int TEST_getIndex_d( List* array, double num );
int TEST_getIndex_c( List* array, char num );
#define TEST_getIndex(arr, elem) _Generic( (elem), \
                                int: TEST_getIndex_i, \
                               char: TEST_getIndex_c, \
                             double: TEST_getIndex_d )(arr, elem)

/*
 * Testing the setValue() function
 */
int TEST_setValue_i( List* array, int num, int idx );
int TEST_setValue_d( List* array, double num, int idx );
int TEST_setValue_c( List* array, char num, int idx );
#define TEST_setValue(arr, num, idx) _Generic( (num), \
                                int: TEST_setValue_i, \
                               char: TEST_setValue_c, \
                             double: TEST_setValue_d )(arr, num, idx)
/*
 * Testing the getElement() function
 */
int TEST_getElement_i( List* array, int index, int dtype );
int TEST_getElement_d( List* array, int index, double dtype );
int TEST_getElement_c( List* array, int index, char dtype );
#define TEST_getElement(arr, idx, elem) _Generic( (elem), \
                                int: TEST_getElement_i, \
                               char: TEST_getElement_c, \
                             double: TEST_getElement_d )(arr, idx, elem)

/*
 * Testing the getLength() function
 */
int TEST_getLength_i( List* array, int dtype );
int TEST_getLength_d( List* array, double dtype );
int TEST_getLength_c( List* array, char dtype );
#define TEST_getLength(arr, dtype) _Generic( (dtype), \
                                int: TEST_getLength_i, \
                               char: TEST_getLength_c, \
                             double: TEST_getLength_d )(arr, dtype)

/*
 * Testing the listRepr() function
 */
int TEST_listRepr_i( List* array, int dtype );
int TEST_listRepr_d( List* array, double dtype );
int TEST_listRepr_c( List* array, char dtype );
#define TEST_listRepr(arr, elem) _Generic( (elem), \
                                int: TEST_listRepr_i, \
                               char: TEST_listRepr_c, \
                             double: TEST_listRepr_d )(arr, elem)

/*
 * Testing the printList() function
 */
int TEST_printList_i( List* array, int dtype );
int TEST_printList_d( List* array, double dtype );
int TEST_printList_c( List* array, char dtype );
#define TEST_printList(arr, elem) _Generic( (elem), \
                                int: TEST_printList_i, \
                               char: TEST_printList_c, \
                             double: TEST_printList_d )(arr, elem)

/*
 * Function to create test arrays
 */
List* makeTestList_i(); 
List* makeTestList_d();
List* makeTestList_c(); 
#define makeTestList(elem) _Generic( (elem), \
                                int: makeTestList_i, \
                               char: makeTestList_c, \
                             double: makeTestList_d )()

#endif
