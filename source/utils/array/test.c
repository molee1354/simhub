#include <stdio.h>
#include <stdlib.h>

#include "test.h"
#include "array.h"


// test result tracker
static int testSuccess = 0;
static int testFail = 0;

// arrays for testing
int    ref_testArray_i[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
double ref_testArray_d[] = {0., 1., 2., 3., 4., 5., 6., 7., 8., 9.};
char   ref_testArray_c[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
const int    ref_len = 10;

// item to add to array
const int    ref_addItem_i = 999;
const double ref_addItem_d = 999.;
const char   ref_addItem_c = '+';

// type references
#define    INT       ref_addItem_i
#define    DOUBLE    ref_addItem_d
#define    CHAR      ref_addItem_c

// test values for find-type functions
const int  targ_idx = 3;
const int    targ_i = 3;
const double targ_d = 3;
const char   targ_c = 'd';


int TEST_makeArray_i(void) {
    puts("testing makeArray_i(sizeof(int))...");
    Array* testArray = makeArray(sizeof(int));
    if (testArray == NULL) {
        TEST_FAIL("testArray is NULL!");
        return 0;
    } 
    else {
        TEST_SUCCESS();
        freeArray(testArray);
    }
    return 0;
}
int TEST_makeArray_d(void) {
    puts("testing makeArray_d(sizeof(double))...");
    Array* testArray = makeArray(sizeof(double));
    if (testArray == NULL) {
        TEST_FAIL("testArray is NULL!");
        return 0;
    } 
    else {
        TEST_SUCCESS();
        freeArray(testArray);
    }
    return 0;
}
int TEST_makeArray_c(void) {
    puts("testing makeArray_c(sizeof(char))...");
    Array* testArray = makeArray(sizeof(char));
    if (testArray == NULL) {
        TEST_FAIL("testArray is NULL!");
        return 0;
    } 
    else {
        TEST_SUCCESS();
        freeArray(testArray);
    }
    return 0;
}

int TEST_freeArray_i(Array* array, int num) {
    puts("testing freeArray_i(Array* array)...");
    if (!freeArray(array)) { TEST_SUCCESS(); } 
    else { TEST_FAIL("freeArray_i(Array* array) did not return 0"); }
    return 0;
}
int TEST_freeArray_d(Array* array, double num) {
    puts("testing freeArray_d(Array* array)...");
    if (!freeArray(array)) { TEST_SUCCESS(); } 
    else { TEST_FAIL("freeArray_d(Array* array) did not return 0"); }
    return 0;
}
int TEST_freeArray_c(Array* array, char num) {
    puts("testing freeArray_c(Array* array)...");
    if (!freeArray(array)) { TEST_SUCCESS(); } 
    else { TEST_FAIL("freeArray_c(Array* array) did not return 0"); }
    return 0;
}


int TEST_getLength_i( Array* array, int dtype ) {
    puts("testing getLength_i(Array* array)...");
    printf("\t* Array : "); printArray(array);
    printf("\t* ref length (constant)   : %d\n", ref_len);
    printf("\t* getLength(Array* array) : %d\n", getLength(array));
    if (getLength(array)==ref_len) { TEST_SUCCESS(); }
    else { TEST_FAIL("getLength(Array* array) did not return the correct length"); }
    return 0;
}
int TEST_getLength_d( Array* array, double dtype ) {
    puts("testing getLength_d(Array* array)...");
    printf("\t* Array : "); printArray(array);
    printf("\t* ref length (constant)   : %d\n", ref_len);
    printf("\t* getLength(Array* array) : %d\n", getLength(array));
    if (getLength(array)==ref_len) { TEST_SUCCESS(); }
    else { TEST_FAIL("getLength(Array* array) did not return the correct length"); }
    return 0;
}
int TEST_getLength_c( Array* array, char dtype ) {
    puts("testing getLength_c(Array* array)...");
    printf("\t* Array : "); printArray(array);
    printf("\t* ref length (constant)   : %d\n", ref_len);
    printf("\t* getLength(Array* array) : %d\n", getLength(array));
    if (getLength(array)==ref_len) { TEST_SUCCESS(); }
    else { TEST_FAIL("getLength(Array* array) did not return the correct length"); }
    return 0;
}

int TEST_append_i( Array* array, int num ) {
    printf("testing append_i(Array* array, int num) for num = %d...\n", num);

    const int pre = getLength(array);
    printf("\t* pre-append  (length : %d) : ", pre);
    printArray(array);

    printf("\t* appending [%d]\n", num);
    append(array, num);
    const int post = getLength(array);
    printf("\t* post-append (length : %d) : ", post);
    printArray(array);

    if ( post<=pre ) {
        TEST_FAIL("append did not change the length of the array");
    } else if (getElement_i(array, post-1) != num ) {
        TEST_FAIL("append did not add the element to the end of the array");
    } else {TEST_SUCCESS();}
    return 0;
}
int TEST_append_d( Array* array, double num ) {
    printf("testing append_i(Array* array, double num) for num = %.2f...\n", num);

    const int pre = getLength(array);
    printf("\t* pre-append  (length : %d) : ", pre);
    printArray(array);

    printf("\t* appending [%.2f]\n", num);
    append(array, num);
    const int post = getLength(array);
    printf("\t* post-append (length : %d) : ", post);
    printArray(array);

    if ( post<=pre ) {
        TEST_FAIL("append did not change the length of the array");
    } else if (getElement_d(array, post-1) != num ) {
        TEST_FAIL("append did not add the element to the end of the array");
    } else {TEST_SUCCESS();}
    return 0;
}
int TEST_append_c( Array* array, char num ) {
    printf("testing append_i(Array* array, char num) for num = %c...\n", num);

    const int pre = getLength(array);
    printf("\t* pre-append  (length : %d) : ", pre);
    printArray(array);

    printf("\t* appending [%c]\n", num);
    append(array, num);
    const int post = getLength(array);
    printf("\t* post-append (length : %d) : ", post);
    printArray(array);

    if ( post<=pre ) {
        TEST_FAIL("append did not change the length of the array");
    } else if (getElement_c(array, post-1) != num ) {
        TEST_FAIL("append did not add the element to the end of the array");
    } else {TEST_SUCCESS();}
    return 0;
}

int TEST_prepend_i( Array* array, int num ) {
    printf("testing prepend_i(Array* array, int num) for num = %d...\n", num);

    const int pre = getLength(array);
    printf("\t* pre-prepend  (length : %d) : ", pre);
    printArray(array);

    printf("\t* prepending [%d]\n", num);
    prepend(array, num);
    const int post = getLength(array);
    printf("\t* post-prepend (length : %d) : ", post);
    printArray(array);

    if ( post<=pre ) {
        TEST_FAIL("prepend did not change the length of the array");
    } else if (getElement_i(array, 0) != num ) {
        TEST_FAIL("prepend did not add the element to the beginning of the array");
    } else {TEST_SUCCESS();}
    return 0;
}
int TEST_prepend_d( Array* array, double num ) {
    printf("testing prepend_d(Array* array, double num) for num = %.2f...\n", num);

    const int pre = getLength(array);
    printf("\t* pre-prepend  (length : %d) : ", pre);
    printArray(array);

    printf("\t* prepending [%.2f]\n", num);
    prepend(array, num);
    const int post = getLength(array);
    printf("\t* post-prepend (length : %d) : ", post);
    printArray(array);

    if ( post<=pre ) {
        TEST_FAIL("prepend did not change the length of the array");
    } else if (getElement_d(array, 0) != num ) {
        TEST_FAIL("prepend did not add the element to the beginning of the array");
    } else {TEST_SUCCESS();}
    return 0;
}
int TEST_prepend_c( Array* array, char num ) {
    printf("testing prepend_c(Array* array, char num) for num = %c...\n", num);

    const int pre = getLength(array);
    printf("\t* pre-prepend  (length : %d) : ", pre);
    printArray(array);

    printf("\t* prepending [%c]\n", num);
    prepend(array, num);
    const int post = getLength(array);
    printf("\t* post-prepend (length : %d) : ", post);
    printArray(array);

    if ( post<=pre ) {
        TEST_FAIL("prepend did not change the length of the array");
    } else if (getElement_c(array, 0) != num ) {
        TEST_FAIL("prepend did not add the element to the beginning of the array");
    } else {TEST_SUCCESS();}
    return 0;
}

int TEST_getElement_i( Array* array, int index, int dtype ) {
    printf("testing getElement_i(Array* array, int index) for index : %d...\n", index);
    printf("\t* reference array : ");
    printf("{");
    int i;
    for (i=0; i<ref_len-1; i++) {
        printf("%d, ", ref_testArray_i[i]);
    } printf("%d}\n", ref_testArray_i[i]);
    printf("\t*      test array : ");
    printArray(array);
    int refEle = ref_testArray_i[index];
    int arrEle = getElement_i(array, index);
    printf("\t* reference array [%d] : %d\n", index, refEle);
    printf("\t*      test array [%d] : %d\n", index, arrEle);
    if ( refEle != arrEle ) {
        TEST_FAIL("getElement did not index the correct element");
    } else { TEST_SUCCESS(); }

    return 0;
}
int TEST_getElement_d( Array* array, int index, double dtype ) {
    printf("testing getElement_d(Array* array, int index) for index : %d...\n", index);
    printf("\t* reference array : ");
    printf("{");
    int i;
    for (i=0; i<ref_len-1; i++) {
        printf("%.2f, ", ref_testArray_d[i]);
    } printf("%.2f}\n", ref_testArray_d[i]);
    printf("\t*      test array : ");
    printArray(array);
    double refEle = ref_testArray_d[index];
    double arrEle = getElement_d(array, index);
    printf("\t* reference array [%d] : %.2f\n", index, refEle);
    printf("\t*      test array [%d] : %.2f\n", index, arrEle);
    if ( refEle != arrEle ) {
        TEST_FAIL("getElement did not index the correct element");
    } else { TEST_SUCCESS(); }

    return 0;
}
int TEST_getElement_c( Array* array, int index, char dtype ) {
    printf("testing getElement_c(Array* array, int index) for index : %d...\n", index);
    printf("\t* reference array : ");
    printf("{");
    int i;
    for (i=0; i<ref_len-1; i++) {
        printf("%c, ", ref_testArray_c[i]);
    } printf("%c}\n", ref_testArray_c[i]);
    printf("\t*      test array : ");
    printArray(array);
    char refEle = ref_testArray_c[index];
    char arrEle = getElement_c(array, index);
    printf("\t* reference array [%d] : %c\n", index, refEle);
    printf("\t*      test array [%d] : %c\n", index, arrEle);
    if ( refEle != arrEle ) {
        TEST_FAIL("getElement did not index the correct element");
    } else { TEST_SUCCESS(); }

    return 0;

}

int TEST_getIndex_i( Array* array, int num ) {
    printf("testing getIndex_i(Array* array, int num) for %d...\n", num);
    printf("\t*      test array : ");
    printArray(array);
    int refIdx = 0;
    int arrIdx = getIndex(array, num);
    while (refIdx<ref_len) {
        if ( ref_testArray_i[refIdx] == num ){ break; }
        refIdx++;
    }
    printf("\t*          index of %d at ref : [%d]\n", num, refIdx);
    printf("\t* index of %d with getIndex_i : [%d]\n", num, arrIdx);
    if ( refIdx != arrIdx ) {
        TEST_FAIL("getElement did not index the correct element");
    } else { TEST_SUCCESS(); }

    return 0;
}
int TEST_getIndex_d( Array* array, double num ) {
    printf("testing getIndex_i(Array* array, int num) for %.2f...\n", num);
    printf("\t*      test array : ");
    printArray(array);
    int refIdx = 0;
    int arrIdx = getIndex(array, num);
    while (refIdx<ref_len) {
        if ( ref_testArray_d[refIdx] == num ){ break; }
        refIdx++;
    }
    printf("\t*          index of %.2f at ref : [%d]\n", num, refIdx);
    printf("\t* index of %.2f with getIndex_i : [%d]\n", num, arrIdx);
    if ( refIdx != arrIdx ) {
        TEST_FAIL("getElement did not index the correct element");
    } else { TEST_SUCCESS(); }

    return 0;
}
int TEST_getIndex_c( Array* array, char num ) {
    printf("testing getIndex_i(Array* array, int num) for %c...\n", num);
    printf("\t*      test array : ");
    printArray(array);
    int refIdx = 0;
    int arrIdx = getIndex(array, num);
    while (refIdx<ref_len) {
        if ( ref_testArray_c[refIdx] == num ){ break; }
        refIdx++;
    }
    printf("\t*          index of %c at ref : [%d]\n", num, refIdx);
    printf("\t* index of %c with getIndex_i : [%d]\n", num, arrIdx);
    if ( refIdx != arrIdx ) {
        TEST_FAIL("getElement did not index the correct element");
    } else { TEST_SUCCESS(); }

    return 0;
}

int TEST_deleteHead_i( Array* array, int dtype ) {
    puts("testing deleteHead_i(Array* array)...");

    const int pre = getLength(array);
    const int prevHead = getElement_i(array, 0);
    printf("\t* pre-delete  (length : %d) : ", pre);
    printArray(array);

    printf("\t* deleting Head [%d]\n", getElement_i(array, 0));
    deleteHead(array);
    const int post = getLength(array);
    const int postHead = getElement_i(array, 0);
    printf("\t* post-delete (length : %d) : ", post);
    printArray(array);

    if ( post>=pre ) {
        TEST_FAIL("deleteHead did not change the length of the array");
    } else if (prevHead == postHead ) {
        TEST_FAIL("deleteHead did not delete the element to the beginning of the array");
    } else {TEST_SUCCESS();}
    return 0;

}
int TEST_deleteHead_d( Array* array, double dtype ) {
    puts("testing deleteHead_i(Array* array)...");

    const int pre = getLength(array);
    const double prevHead = getElement_d(array, 0);
    printf("\t* pre-delete  (length : %d) : ", pre);
    printArray(array);

    printf("\t* deleting Head [%.2f]\n", getElement_d(array, 0));
    deleteHead(array);
    const int post = getLength(array);
    const double postHead = getElement_d(array, 0);
    printf("\t* post-delete (length : %d) : ", post);
    printArray(array);

    if ( post>=pre ) {
        TEST_FAIL("deleteHead did not change the length of the array");
    } else if (prevHead == postHead ) {
        TEST_FAIL("deleteHead did not delete the element to the beginning of the array");
    } else {TEST_SUCCESS();}
    return 0;
}
int TEST_deleteHead_c( Array* array, char dtype ) {
    puts("testing deleteHead_i(Array* array)...");

    const int pre = getLength(array);
    const char prevHead = getElement_c(array, 0);
    printf("\t* pre-delete  (length : %d) : ", pre);
    printArray(array);

    printf("\t* deleting Head [%c]\n", getElement_c(array, 0));
    deleteHead(array);
    const int post = getLength(array);
    const char postHead = getElement_c(array, 0);
    printf("\t* post-delete (length : %d) : ", post);
    printArray(array);

    if ( post>=pre ) {
        TEST_FAIL("deleteHead did not change the length of the array");
    } else if (prevHead == postHead ) {
        TEST_FAIL("deleteHead did not delete the element to the beginning of the array");
    } else {TEST_SUCCESS();}
    return 0;
}

int TEST_deleteTail_i( Array* array, int dtype ) {
    puts("testing deleteTail_i(Array* array)...");

    const int pre = getLength(array);
    const int prevTail = getElement_i(array, pre-1);
    printf("\t* pre-delete  (length : %d) : ", pre);
    printArray(array);

    printf("\t* deleting Tail [%d]\n", prevTail);
    deleteTail(array);
    const int post = getLength(array);
    const int postTail = getElement_i(array, post-1);
    printf("\t* post-delete (length : %d) : ", post);
    printArray(array);

    if ( post>=pre ) {
        TEST_FAIL("deleteTail did not change the length of the array");
    } else if (prevTail == postTail ) {
        TEST_FAIL("deleteTail did not delete the element to the beginning of the array");
    } else {TEST_SUCCESS();}
    return 0;
}
int TEST_deleteTail_d( Array* array, double dtype ) {
    puts("testing deleteTail_i(Array* array)...");

    const int pre = getLength(array);
    const double prevTail = getElement_d(array, pre-1);
    printf("\t* pre-delete  (length : %d) : ", pre);
    printArray(array);

    printf("\t* deleting Tail [%.2f]\n", prevTail);
    deleteTail(array);
    const int post = getLength(array);
    const double postTail = getElement_d(array, post-1);
    printf("\t* post-delete (length : %d) : ", post);
    printArray(array);

    if ( post>=pre ) {
        TEST_FAIL("deleteTail did not change the length of the array");
    } else if (prevTail == postTail ) {
        TEST_FAIL("deleteTail did not delete the element to the beginning of the array");
    } else {TEST_SUCCESS();}
    return 0;
}
int TEST_deleteTail_c( Array* array, char dtype ) {
    puts("testing deleteTail_i(Array* array)...");

    const int pre = getLength(array);
    const char prevTail = getElement_c(array, pre-1);
    printf("\t* pre-delete  (length : %d) : ", pre);
    printArray(array);

    printf("\t* deleting Tail [%c]\n", prevTail);
    deleteTail(array);
    const int post = getLength(array);
    const char postTail = getElement_c(array, post-1);
    printf("\t* post-delete (length : %d) : ", post);
    printArray(array);

    if ( post>=pre ) {
        TEST_FAIL("deleteTail did not change the length of the array");
    } else if (prevTail == postTail ) {
        TEST_FAIL("deleteTail did not delete the element to the beginning of the array");
    } else {TEST_SUCCESS();}
    return 0;
}

int TEST_listRepr_i( Array* array, int dtype ) {
    puts("testing listRepr_i(Array* array)...");
    printf("\t*       array representation : "); printArray(array);
    printf("\t* linked list representation : ");
    if (!listRepr(array)) { TEST_SUCCESS(); }
    else { TEST_FAIL("listRepr_i did not exit successfully"); }
    return 0;
}
int TEST_listRepr_d( Array* array, double dtype ) {
    puts("testing listRepr_d(Array* array)...");
    printf("\t*       array representation : "); printArray(array);
    printf("\t* linked list representation : ");
    if (!listRepr(array)) { TEST_SUCCESS(); }
    else { TEST_FAIL("listRepr_d did not exit successfully"); }
    return 0;
}
int TEST_listRepr_c( Array* array, char dtype ) {
    puts("testing listRepr_c(Array* array)...");
    printf("\t*       array representation : "); printArray(array);
    printf("\t* linked list representation : ");
    if (!listRepr(array)) { TEST_SUCCESS(); }
    else { TEST_FAIL("listRepr_c did not exit successfully"); }
    return 0;
}
/* int TEST_tests(void) {
    Array* myArray = makeArray(sizeof(TYPE));
    puts("array created");

    int length = getLength( myArray );
    printArray( myArray );
    printf("length %d\n", length);

    for (int i = 65; i<80; i++) {
        append(myArray, (TYPE)i);
        printArray( myArray );
    }

    printf("Array length : %d\n", getLength( myArray ));

    puts("\ndeleteTail()");
    deleteTail( myArray );
    printf("Array length : %d\n", getLength( myArray ));
    listRepr( myArray );

    puts("\ndeleteTail()");
    deleteTail( myArray );
    printf("Array length : %d\n", getLength( myArray ));
    listRepr( myArray );

    puts("\ndeleteHead()");
    deleteHead( myArray );
    printf("Array length : %d\n", getLength( myArray ));
    listRepr( myArray );

    TYPE num = 88;
    printf("\nprepend() %d\n", num);
    prepend(myArray, num);
    printf("Array length : %d\n", getLength( myArray ));
    listRepr( myArray );

    TYPE bis = 88;
    printf("\nappend() %d\n", bis);
    append(myArray, bis);
    printf("Array length : %d\n", getLength( myArray ));
    listRepr( myArray );

    const int pos = 3;
    printf("\ngetElement() at %d: %d\n", pos, getElement( myArray, pos ));
    printArray( myArray );

    const int target = 71;
    printf("\nfindIndex() of %d: %d\n", target, findIndex( myArray, target ));
    printArray( myArray );

    puts("\nfreeArray()");
    freeArray( myArray );
} */

Array* makeTestArray_i() {
    Array* testArray_i = makeArray(sizeof(ref_addItem_i));
    for (int i=0; i<ref_len; i++) append(testArray_i, ref_testArray_i[i]);
    return testArray_i;
}
Array* makeTestArray_d() {
    Array* testArray_d = makeArray(sizeof(ref_addItem_d));
    for (int i=0; i<ref_len; i++) append(testArray_d, ref_testArray_d[i]);
    return testArray_d;
}
Array* makeTestArray_c() {
    Array* testArray_c = makeArray(sizeof(ref_addItem_c));
    for (int i=0; i<ref_len; i++) append(testArray_c, ref_testArray_c[i]);
    return testArray_c;
}

int main() {
    /* The failure in one of these tests won't stop the program */
    TEST_makeArray(INT);
    TEST_makeArray(DOUBLE);
    TEST_makeArray(CHAR);

    /* Initializing arrays to do the tests on */
    Array* testArray_i = makeTestArray(INT);
    Array* testArray_d = makeTestArray(DOUBLE);
    Array* testArray_c = makeTestArray(CHAR);

    /* the `get` type functions must be tested before any append/prepend
    function tests are done */
    TEST_getLength(testArray_i, INT);
    TEST_getLength(testArray_d, DOUBLE);
    TEST_getLength(testArray_c, CHAR);

    TEST_getElement(testArray_i, targ_idx, INT);
    TEST_getElement(testArray_d, targ_idx, DOUBLE);
    TEST_getElement(testArray_c, targ_idx, CHAR);

    TEST_getIndex(testArray_i, targ_i);
    TEST_getIndex(testArray_d, targ_d);
    TEST_getIndex(testArray_c, targ_c);

    TEST_append(testArray_i, ref_addItem_i);
    TEST_append(testArray_d, ref_addItem_d);
    TEST_append(testArray_c, ref_addItem_c);

    TEST_prepend(testArray_i, ref_addItem_i);
    TEST_prepend(testArray_d, ref_addItem_d);
    TEST_prepend(testArray_c, ref_addItem_c);

    TEST_deleteHead(testArray_i, INT);
    TEST_deleteHead(testArray_d, DOUBLE);
    TEST_deleteHead(testArray_c, CHAR);

    TEST_deleteTail(testArray_i, INT);
    TEST_deleteTail(testArray_d, DOUBLE);
    TEST_deleteTail(testArray_c, CHAR);

    TEST_listRepr(testArray_i, INT);
    TEST_listRepr(testArray_d, DOUBLE);
    TEST_listRepr(testArray_c, CHAR);

    TEST_freeArray(testArray_i, INT);
    TEST_freeArray(testArray_d, DOUBLE);
    TEST_freeArray(testArray_c, CHAR);

    printf("[RESULT] : %d out of %d tests passed.\n\n", testSuccess, testSuccess+testFail);

    return 0;
}
