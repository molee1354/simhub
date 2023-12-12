#include <stdio.h>
#include <stdlib.h>

#include "test.h"
#include "array.h"
#include "../src/array.h"


// test result tracker
static int testSuccess = 0;
static int testFail = 0;

// arrays for testing
int    ref_testList_i[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
double ref_testList_d[] = {0., 1., 2., 3., 4., 5., 6., 7., 8., 9.};
char   ref_testList_c[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
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
const int    swap_idx = 7;
const int    targ_idx = 3;

const int    targ_i = 3;
const double targ_d = 3;
const char   targ_c = 'd';

const int    swap_targ_i = 99;
const double swap_targ_d = 99.;
const char   swap_targ_c = '*';


int TEST_makeList_i(void) {
    puts("testing makeList_i(sizeof(int))...");
    List* testList = makeList(sizeof(int));
    if (testList == NULL) {
        TEST_FAIL("testList is NULL!");
        return 1;
    } 
    else {
        TEST_SUCCESS();
        freeList(testList);
    }
    return 0;
}
int TEST_makeList_d(void) {
    puts("testing makeList_d(sizeof(double))...");
    List* testList = makeList(sizeof(double));
    if (testList == NULL) {
        TEST_FAIL("testList is NULL!");
        return 1;
    } 
    else {
        TEST_SUCCESS();
        freeList(testList);
    }
    return 0;
}
int TEST_makeList_c(void) {
    puts("testing makeList_c(sizeof(char))...");
    List* testList = makeList(sizeof(char));
    if (testList == NULL) {
        TEST_FAIL("testList is NULL!");
        return 1;
    } 
    else {
        TEST_SUCCESS();
        freeList(testList);
    }
    return 0;
}

int TEST_toList_i(void) {
    puts("testing toList_i(sizeof(int))...");
    List* testList = toList_i( ref_testList_i, ref_len );
    printf("\t*   test List : "); 
    printf("[");
    for (int i=0; i<ref_len-1; i++) {printf("%d, ", ref_testList_i[i]);}
    printf("%d]\n", ref_testList_i[ref_len-1]);
    printf("\t* normal List : "); printList(testList);
    if (testList == NULL) {
        TEST_FAIL("testList is NULL!");
        return 1;
    } 
    else {
        TEST_SUCCESS();
        freeList(testList);
    }
    return 0;
}
int TEST_toList_d(void) {
    puts("testing toList_d(sizeof(double))...");
    List* testList = toList_d( ref_testList_d, ref_len );
    printf("\t*   test List : "); 
    printf("[");
    for (int i=0; i<ref_len-1; i++) {printf("%.2f, ", ref_testList_d[i]);}
    printf("%.2f]\n", ref_testList_d[ref_len-1]);
    printf("\t* normal List : "); printList(testList);
    if (testList == NULL) {
        TEST_FAIL("testList is NULL!");
        return 1;
    } 
    else {
        TEST_SUCCESS();
        freeList(testList);
    }
    return 0;
}
int TEST_toList_c(void) {
    puts("testing toList_c(sizeof(char))...");
    List* testList = toList_c( ref_testList_c, ref_len );
    printf("\t*   test List : "); 
    printf("[");
    for (int i=0; i<ref_len-1; i++) {printf("%c, ", ref_testList_c[i]);}
    printf("%c]\n", ref_testList_c[ref_len-1]);
    printf("\t* normal List : "); printList(testList);
    if (testList == NULL) {
        TEST_FAIL("testList is NULL!");
        return 1;
    } 
    else {
        TEST_SUCCESS();
        freeList(testList);
    }
    return 0;
}

int TEST_freeList_i(List* array, int num) {
    puts("testing freeList_i(List* array)...");
    if (!freeList(array)) { TEST_SUCCESS(); } 
    else {
        TEST_FAIL("freeList_c(List* array) did not return 0");
        return 1;
    }
    return 0;
}
int TEST_freeList_d(List* array, double num) {
    puts("testing freeList_d(List* array)...");
    if (!freeList(array)) { TEST_SUCCESS(); } 
    else {
        TEST_FAIL("freeList_c(List* array) did not return 0");
        return 1;
    }
    return 0;
}
int TEST_freeList_c(List* array, char num) {
    puts("testing freeList_c(List* array)...");
    if (!freeList(array)) { TEST_SUCCESS(); } 
    else {
        TEST_FAIL("freeList_c(List* array) did not return 0");
        return 1;
    }
    return 0;
}


int TEST_getLength_i( List* array, int dtype ) {
    puts("testing getLength_i(List* array)...");
    printf("\t* List : "); printList(array);
    printf("\t* ref length (constant)   : %d\n", ref_len);
    printf("\t* getLength(List* array) : %d\n", getLength(array));
    if (getLength(array)==ref_len) { TEST_SUCCESS(); }
    else {
        TEST_FAIL("getLength(List* array) did not return the correct length");
        return 1;
    }
    return 0;
}
int TEST_getLength_d( List* array, double dtype ) {
    puts("testing getLength_d(List* array)...");
    printf("\t* List : "); printList(array);
    printf("\t* ref length (constant)   : %d\n", ref_len);
    printf("\t* getLength(List* array) : %d\n", getLength(array));
    if (getLength(array)==ref_len) { TEST_SUCCESS(); }
    else {
        TEST_FAIL("getLength(List* array) did not return the correct length");
        return 1;
    }
    return 0;
}
int TEST_getLength_c( List* array, char dtype ) {
    puts("testing getLength_c(List* array)...");
    printf("\t* List : "); printList(array);
    printf("\t* ref length (constant)   : %d\n", ref_len);
    printf("\t* getLength(List* array) : %d\n", getLength(array));
    if (getLength(array)==ref_len) { TEST_SUCCESS(); }
    else {
        TEST_FAIL("getLength(List* array) did not return the correct length");
        return 1;
    }
    return 0;
}

int TEST_append_i( List* array, int num ) {
    printf("testing append_i(List* array, int num) for num = %d...\n", num);

    const int pre = getLength(array);
    printf("\t* pre-append  (length : %d) : ", pre);
    printList(array);

    printf("\t* appending [%d]\n", num);
    append(array, num);
    const int post = getLength(array);
    printf("\t* post-append (length : %d) : ", post);
    printList(array);

    if ( post<=pre ) {
        TEST_FAIL("append did not change the length of the array");
        return 1;
    } else if (getElement_i(array, post-1) != num ) {
        TEST_FAIL("append did not add the element to the end of the array");
        return 1;
    } else {TEST_SUCCESS();}
    return 0;
}
int TEST_append_d( List* array, double num ) {
    printf("testing append_i(List* array, double num) for num = %.2f...\n", num);

    const int pre = getLength(array);
    printf("\t* pre-append  (length : %d) : ", pre);
    printList(array);

    printf("\t* appending [%.2f]\n", num);
    append(array, num);
    const int post = getLength(array);
    printf("\t* post-append (length : %d) : ", post);
    printList(array);

    if ( post<=pre ) {
        TEST_FAIL("append did not change the length of the array");
        return 1;
    } else if (getElement_d(array, post-1) != num ) {
        TEST_FAIL("append did not add the element to the end of the array");
        return 1;
    } else {TEST_SUCCESS();}
    return 0;
}
int TEST_append_c( List* array, char num ) {
    printf("testing append_i(List* array, char num) for num = %c...\n", num);

    const int pre = getLength(array);
    printf("\t* pre-append  (length : %d) : ", pre);
    printList(array);

    printf("\t* appending [%c]\n", num);
    append(array, num);
    const int post = getLength(array);
    printf("\t* post-append (length : %d) : ", post);
    printList(array);

    if ( post<=pre ) {
        TEST_FAIL("append did not change the length of the array");
        return 1;
    } else if (getElement_c(array, post-1) != num ) {
        TEST_FAIL("append did not add the element to the end of the array");
        return 1;
    } else {TEST_SUCCESS();}
    return 0;
}

int TEST_prepend_i( List* array, int num ) {
    printf("testing prepend_i(List* array, int num) for num = %d...\n", num);

    const int pre = getLength(array);
    printf("\t* pre-prepend  (length : %d) : ", pre);
    printList(array);

    printf("\t* prepending [%d]\n", num);
    prepend(array, num);
    const int post = getLength(array);
    printf("\t* post-prepend (length : %d) : ", post);
    printList(array);

    if ( post<=pre ) {
        TEST_FAIL("prepend did not change the length of the array");
        return 1;
    } else if (getElement_i(array, 0) != num ) {
        TEST_FAIL("prepend did not add the element to the beginning of the array");
        return 1;
    } else {TEST_SUCCESS();}
    return 0;
}
int TEST_prepend_d( List* array, double num ) {
    printf("testing prepend_d(List* array, double num) for num = %.2f...\n", num);

    const int pre = getLength(array);
    printf("\t* pre-prepend  (length : %d) : ", pre);
    printList(array);

    printf("\t* prepending [%.2f]\n", num);
    prepend(array, num);
    const int post = getLength(array);
    printf("\t* post-prepend (length : %d) : ", post);
    printList(array);

    if ( post<=pre ) {
        TEST_FAIL("prepend did not change the length of the array");
        return 1;
    } else if (getElement_d(array, 0) != num ) {
        TEST_FAIL("prepend did not add the element to the beginning of the array");
        return 1;
    } else {TEST_SUCCESS();}
    return 0;
}
int TEST_prepend_c( List* array, char num ) {
    printf("testing prepend_c(List* array, char num) for num = %c...\n", num);

    const int pre = getLength(array);
    printf("\t* pre-prepend  (length : %d) : ", pre);
    printList(array);

    printf("\t* prepending [%c]\n", num);
    prepend(array, num);
    const int post = getLength(array);
    printf("\t* post-prepend (length : %d) : ", post);
    printList(array);

    if ( post<=pre ) {
        TEST_FAIL("prepend did not change the length of the array");
        return 1;
    } else if (getElement_c(array, 0) != num ) {
        TEST_FAIL("prepend did not add the element to the beginning of the array");
        return 1;
    } else {TEST_SUCCESS();}
    return 0;
}

int TEST_getElement_i( List* array, int index, int dtype ) {
    printf("testing getElement_i(List* array, int index) for index : %d...\n", index);
    printf("\t* reference array : ");
    printf("{");
    int i;
    for (i=0; i<ref_len-1; i++) {
        printf("%d, ", ref_testList_i[i]);
    } printf("%d}\n", ref_testList_i[i]);
    printf("\t*      test array : ");
    printList(array);
    int refEle = ref_testList_i[index];
    int arrEle = getElement_i(array, index);
    printf("\t* reference array [%d] : %d\n", index, refEle);
    printf("\t*      test array [%d] : %d\n", index, arrEle);
    if ( refEle != arrEle ) {
        TEST_FAIL("getElement did not index the correct element");
        return 1;
    } else { TEST_SUCCESS(); }
    return 0;
}
int TEST_getElement_d( List* array, int index, double dtype ) {
    printf("testing getElement_d(List* array, int index) for index : %d...\n", index);
    printf("\t* reference array : ");
    printf("{");
    int i;
    for (i=0; i<ref_len-1; i++) {
        printf("%.2f, ", ref_testList_d[i]);
    } printf("%.2f}\n", ref_testList_d[i]);
    printf("\t*      test array : ");
    printList(array);
    double refEle = ref_testList_d[index];
    double arrEle = getElement_d(array, index);
    printf("\t* reference array [%d] : %.2f\n", index, refEle);
    printf("\t*      test array [%d] : %.2f\n", index, arrEle);
    if ( refEle != arrEle ) {
        TEST_FAIL("getElement did not index the correct element");
        return 1;
    } else { TEST_SUCCESS(); }
    return 0;
}
int TEST_getElement_c( List* array, int index, char dtype ) {
    printf("testing getElement_c(List* array, int index) for index : %d...\n", index);
    printf("\t* reference array : ");
    printf("{");
    int i;
    for (i=0; i<ref_len-1; i++) {
        printf("%c, ", ref_testList_c[i]);
    } printf("%c}\n", ref_testList_c[i]);
    printf("\t*      test array : ");
    printList(array);
    char refEle = ref_testList_c[index];
    char arrEle = getElement_c(array, index);
    printf("\t* reference array [%d] : %c\n", index, refEle);
    printf("\t*      test array [%d] : %c\n", index, arrEle);
    if ( refEle != arrEle ) {
        TEST_FAIL("getElement did not index the correct element");
        return 1;
    } else { TEST_SUCCESS(); }
    return 0;
}

int TEST_getIndex_i( List* array, int num ) {
    printf("testing getIndex_i(List* array, int num) for %d...\n", num);
    printf("\t*      test array : ");
    printList(array);
    int refIdx = 0;
    int arrIdx = getIndex(array, num);
    while (refIdx<ref_len) {
        if ( ref_testList_i[refIdx] == num ){ break; }
        refIdx++;
    }
    printf("\t*          index of %d at ref : [%d]\n", num, refIdx);
    printf("\t* index of %d with getIndex_i : [%d]\n", num, arrIdx);
    if ( refIdx != arrIdx ) {
        TEST_FAIL("getElement did not index the correct element");
        return 1;
    } else { TEST_SUCCESS(); }
    return 0;
}
int TEST_getIndex_d( List* array, double num ) {
    printf("testing getIndex_i(List* array, int num) for %.2f...\n", num);
    printf("\t*      test array : ");
    printList(array);
    int refIdx = 0;
    int arrIdx = getIndex(array, num);
    while (refIdx<ref_len) {
        if ( ref_testList_d[refIdx] == num ){ break; }
        refIdx++;
    }
    printf("\t*          index of %.2f at ref : [%d]\n", num, refIdx);
    printf("\t* index of %.2f with getIndex_i : [%d]\n", num, arrIdx);
    if ( refIdx != arrIdx ) {
        TEST_FAIL("getElement did not index the correct element");
        return 1;
    } else { TEST_SUCCESS(); }
    return 0;
}
int TEST_getIndex_c( List* array, char num ) {
    printf("testing getIndex_i(List* array, int num) for %c...\n", num);
    printf("\t*      test array : ");
    printList(array);
    int refIdx = 0;
    int arrIdx = getIndex(array, num);
    while (refIdx<ref_len) {
        if ( ref_testList_c[refIdx] == num ){ break; }
        refIdx++;
    }
    printf("\t*          index of %c at ref : [%d]\n", num, refIdx);
    printf("\t* index of %c with getIndex_i : [%d]\n", num, arrIdx);
    if ( refIdx != arrIdx ) {
        TEST_FAIL("getElement did not index the correct element");
        return 1;
    } else { TEST_SUCCESS(); }
    return 0;
}

int TEST_setValue_i( List* array, int num, int idx ) {
    printf("testing setValue_i(List* array, int num, int idx) for num %d at idx [%d]\n", num, idx);
    printf("\t*     test array : ");
    printList(array);
    int prevEle = getElement_i(array, idx);
    setValue_i(array, num, idx);
    int postEle = getElement_i(array, idx);
    printf("\t* modified array : ");
    printList(array);

    if ( prevEle == postEle ) {
        TEST_FAIL("setValue did not change the value");
        return 1;
    } else if ( getElement_i(array, idx)!=num ) {
        TEST_FAIL("setValue did not change to the right value");
        return 1;
    } else { TEST_SUCCESS(); }
    return 0;
}
int TEST_setValue_d( List* array, double num, int idx ) {
    printf("testing setValue_d(List* array, double num, int idx) for num %.2f at idx [%d]\n", num, idx);
    printf("\t*     test array : ");
    printList(array);
    double prevEle = getElement_d(array, idx);
    setValue_d(array, num, idx);
    double postEle = getElement_d(array, idx);
    printf("\t* modified array : ");
    printList(array);

    if ( prevEle == postEle ) {
        TEST_FAIL("setValue did not change the value");
        return 1;
    } else if ( getElement_d(array, idx)!=num ) {
        TEST_FAIL("setValue did not change to the right value");
        return 1;
    } else { TEST_SUCCESS(); }
    return 0;
}
int TEST_setValue_c( List* array, char num, int idx ) {
    printf("testing setValue_c(List* array, char num, int idx) for num %c at idx [%d]\n", num, idx);
    printf("\t*     test array : ");
    printList(array);
    char prevEle = getElement_c(array, idx);
    setValue_c(array, num, idx);
    char postEle = getElement_c(array, idx);
    printf("\t* modified array : ");
    printList(array);

    if ( prevEle == postEle ) {
        TEST_FAIL("setValue did not change the value");
        return 1;
    } else if ( getElement_c(array, idx)!=num ) {
        TEST_FAIL("setValue did not change to the right value");
        return 1;
    } else { TEST_SUCCESS(); }
    return 0;
}

int TEST_deleteHead_i( List* array, int dtype ) {
    puts("testing deleteHead_i(List* array)...");

    const int pre = getLength(array);
    const int prevHead = getElement_i(array, 0);
    printf("\t* pre-delete  (length : %d) : ", pre);
    printList(array);

    printf("\t* deleting Head [%d]\n", getElement_i(array, 0));
    deleteHead(array);
    const int post = getLength(array);
    const int postHead = getElement_i(array, 0);
    printf("\t* post-delete (length : %d) : ", post);
    printList(array);

    if ( post>=pre ) {
        TEST_FAIL("deleteHead did not change the length of the array");
        return 1;
    } else if (prevHead == postHead ) {
        TEST_FAIL("deleteHead did not delete the element to the beginning of the array");
        return 1;
    } else {TEST_SUCCESS();}
    return 0;

}
int TEST_deleteHead_d( List* array, double dtype ) {
    puts("testing deleteHead_i(List* array)...");

    const int pre = getLength(array);
    const double prevHead = getElement_d(array, 0);
    printf("\t* pre-delete  (length : %d) : ", pre);
    printList(array);

    printf("\t* deleting Head [%.2f]\n", getElement_d(array, 0));
    deleteHead(array);
    const int post = getLength(array);
    const double postHead = getElement_d(array, 0);
    printf("\t* post-delete (length : %d) : ", post);
    printList(array);

    if ( post>=pre ) {
        TEST_FAIL("deleteHead did not change the length of the array");
        return 1;
    } else if (prevHead == postHead ) {
        TEST_FAIL("deleteHead did not delete the element to the beginning of the array");
        return 1;
    } else {TEST_SUCCESS();}
    return 0;
}
int TEST_deleteHead_c( List* array, char dtype ) {
    puts("testing deleteHead_i(List* array)...");

    const int pre = getLength(array);
    const char prevHead = getElement_c(array, 0);
    printf("\t* pre-delete  (length : %d) : ", pre);
    printList(array);

    printf("\t* deleting Head [%c]\n", getElement_c(array, 0));
    deleteHead(array);
    const int post = getLength(array);
    const char postHead = getElement_c(array, 0);
    printf("\t* post-delete (length : %d) : ", post);
    printList(array);

    if ( post>=pre ) {
        TEST_FAIL("deleteHead did not change the length of the array");
        return 1;
    } else if (prevHead == postHead ) {
        TEST_FAIL("deleteHead did not delete the element to the beginning of the array");
        return 1;
    } else {TEST_SUCCESS();}
    return 0;
}

int TEST_deleteTail_i( List* array, int dtype ) {
    puts("testing deleteTail_i(List* array)...");

    const int pre = getLength(array);
    const int prevTail = getElement_i(array, pre-1);
    printf("\t* pre-delete  (length : %d) : ", pre);
    printList(array);

    printf("\t* deleting Tail [%d]\n", prevTail);
    deleteTail(array);
    const int post = getLength(array);
    const int postTail = getElement_i(array, post-1);
    printf("\t* post-delete (length : %d) : ", post);
    printList(array);

    if ( post>=pre ) {
        TEST_FAIL("deleteTail did not change the length of the array");
        return 1;
    } else if (prevTail == postTail ) {
        TEST_FAIL("deleteTail did not delete the element to the beginning of the array");
        return 1;
    } else {TEST_SUCCESS();}
    return 0;
}
int TEST_deleteTail_d( List* array, double dtype ) {
    puts("testing deleteTail_i(List* array)...");

    const int pre = getLength(array);
    const double prevTail = getElement_d(array, pre-1);
    printf("\t* pre-delete  (length : %d) : ", pre);
    printList(array);

    printf("\t* deleting Tail [%.2f]\n", prevTail);
    deleteTail(array);
    const int post = getLength(array);
    const double postTail = getElement_d(array, post-1);
    printf("\t* post-delete (length : %d) : ", post);
    printList(array);

    if ( post>=pre ) {
        TEST_FAIL("deleteTail did not change the length of the array");
        return 1;
    } else if (prevTail == postTail ) {
        TEST_FAIL("deleteTail did not delete the element to the beginning of the array");
        return 1;
    } else {TEST_SUCCESS();}
    return 0;
}
int TEST_deleteTail_c( List* array, char dtype ) {
    puts("testing deleteTail_i(List* array)...");

    const int pre = getLength(array);
    const char prevTail = getElement_c(array, pre-1);
    printf("\t* pre-delete  (length : %d) : ", pre);
    printList(array);

    printf("\t* deleting Tail [%c]\n", prevTail);
    deleteTail(array);
    const int post = getLength(array);
    const char postTail = getElement_c(array, post-1);
    printf("\t* post-delete (length : %d) : ", post);
    printList(array);

    if ( post>=pre ) {
        TEST_FAIL("deleteTail did not change the length of the array");
        return 1;
    } else if (prevTail == postTail ) {
        TEST_FAIL("deleteTail did not delete the element to the beginning of the array");
        return 1;
    } else {TEST_SUCCESS();}
    return 0;
}

int TEST_listRepr_i( List* array, int dtype ) {
    puts("testing listRepr_i(List* array)...");
    printf("\t*       array representation : "); printList(array);
    printf("\t* linked list representation : ");
    if (!listRepr(array)) { TEST_SUCCESS(); }
    else {
        TEST_FAIL("listRepr_i did not exit successfully");
        return 1;
    }
    return 0;
}
int TEST_listRepr_d( List* array, double dtype ) {
    puts("testing listRepr_d(List* array)...");
    printf("\t*       array representation : "); printList(array);
    printf("\t* linked list representation : ");
    if (!listRepr(array)) { TEST_SUCCESS(); }
    else {
        TEST_FAIL("listRepr_i did not exit successfully");
        return 1;
    }
    return 0;
}
int TEST_listRepr_c( List* array, char dtype ) {
    puts("testing listRepr_c(List* array)...");
    printf("\t*       array representation : "); printList(array);
    printf("\t* linked list representation : ");
    if (!listRepr(array)) { TEST_SUCCESS(); }
    else {
        TEST_FAIL("listRepr_i did not exit successfully");
        return 1;
    }
    return 0;
}
/* int TEST_tests(void) {
    List* myList = makeList(sizeof(TYPE));
    puts("array created");

    int length = getLength( myList );
    printList( myList );
    printf("length %d\n", length);

    for (int i = 65; i<80; i++) {
        append(myList, (TYPE)i);
        printList( myList );
    }

    printf("List length : %d\n", getLength( myList ));

    puts("\ndeleteTail()");
    deleteTail( myList );
    printf("List length : %d\n", getLength( myList ));
    listRepr( myList );

    puts("\ndeleteTail()");
    deleteTail( myList );
    printf("List length : %d\n", getLength( myList ));
    listRepr( myList );

    puts("\ndeleteHead()");
    deleteHead( myList );
    printf("List length : %d\n", getLength( myList ));
    listRepr( myList );

    TYPE num = 88;
    printf("\nprepend() %d\n", num);
    prepend(myList, num);
    printf("List length : %d\n", getLength( myList ));
    listRepr( myList );

    TYPE bis = 88;
    printf("\nappend() %d\n", bis);
    append(myList, bis);
    printf("List length : %d\n", getLength( myList ));
    listRepr( myList );

    const int pos = 3;
    printf("\ngetElement() at %d: %d\n", pos, getElement( myList, pos ));
    printList( myList );

    const int target = 71;
    printf("\nfindIndex() of %d: %d\n", target, findIndex( myList, target ));
    printList( myList );

    puts("\nfreeList()");
    freeList( myList );
} */

List* makeTestList_i() {
    List* testList_i = makeList(sizeof(ref_addItem_i));
    for (int i=0; i<ref_len; i++) append(testList_i, ref_testList_i[i]);
    return testList_i;
}
List* makeTestList_d() {
    List* testList_d = makeList(sizeof(ref_addItem_d));
    for (int i=0; i<ref_len; i++) append(testList_d, ref_testList_d[i]);
    return testList_d;
}
List* makeTestList_c() {
    List* testList_c = makeList(sizeof(ref_addItem_c));
    for (int i=0; i<ref_len; i++) append(testList_c, ref_testList_c[i]);
    return testList_c;
}

int main() {
    /* The failure in one of these tests won't stop the program */
    TEST_makeList(INT);
    TEST_makeList(DOUBLE);
    TEST_makeList(CHAR);

    TEST_toList(INT);
    TEST_toList(DOUBLE);
    TEST_toList(CHAR);

    /* Initializing arrays to do the tests on */
    List* testList_i = makeTestList(INT);
    List* testList_d = makeTestList(DOUBLE);
    List* testList_c = makeTestList(CHAR);

    /* the `get` type functions must be tested before any append/prepend
    function tests are done */
    TEST_getLength(testList_i, INT);
    TEST_getLength(testList_d, DOUBLE);
    TEST_getLength(testList_c, CHAR);

    TEST_getElement(testList_i, targ_idx, INT);
    TEST_getElement(testList_d, targ_idx, DOUBLE);
    TEST_getElement(testList_c, targ_idx, CHAR);

    TEST_setValue(testList_i, swap_targ_i, swap_idx);
    TEST_setValue(testList_d, swap_targ_d, swap_idx);
    TEST_setValue(testList_c, swap_targ_c, swap_idx);

    TEST_getIndex(testList_i, targ_i);
    TEST_getIndex(testList_d, targ_d);
    TEST_getIndex(testList_c, targ_c);

    TEST_append(testList_i, ref_addItem_i);
    TEST_append(testList_d, ref_addItem_d);
    TEST_append(testList_c, ref_addItem_c);

    TEST_prepend(testList_i, ref_addItem_i);
    TEST_prepend(testList_d, ref_addItem_d);
    TEST_prepend(testList_c, ref_addItem_c);

    TEST_deleteHead(testList_i, INT);
    TEST_deleteHead(testList_d, DOUBLE);
    TEST_deleteHead(testList_c, CHAR);

    TEST_deleteTail(testList_i, INT);
    TEST_deleteTail(testList_d, DOUBLE);
    TEST_deleteTail(testList_c, CHAR);

    TEST_listRepr(testList_i, INT);
    TEST_listRepr(testList_d, DOUBLE);
    TEST_listRepr(testList_c, CHAR);

    TEST_freeList(testList_i, INT);
    TEST_freeList(testList_d, DOUBLE);
    TEST_freeList(testList_c, CHAR);

    printf("[RESULT] : %d out of %d tests passed.\n\n", testSuccess, testSuccess+testFail);

    return 0;
}
