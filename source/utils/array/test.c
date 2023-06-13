#include <stdio.h>
#include <stdlib.h>

#include "test.h"
#include "array.h"

Array* TEST_makeArray_i(void) {
    puts("testing makeArray(sizeof(int))...");
    Array* testArray_i = makeArray(sizeof(int));
    if (testArray_i == NULL) { TEST_FAIL("testArray is NULL!"); } 
    else { TEST_SUCCESS(); }
    
    return testArray_i;
}
Array* TEST_makeArray_d(void) {
    puts("testing makeArray(sizeof(double))...");
    Array* testArray_d = makeArray(sizeof(double));
    if (testArray_d == NULL) { TEST_FAIL("testArray is NULL!"); } 
    else { TEST_SUCCESS(); }
    
    return testArray_d;
}
Array* TEST_makeArray_c(void) {
    puts("testing makeArray(sizeof(char))...");
    Array* testArray_c = makeArray(sizeof(char));
    if (testArray_c == NULL) { TEST_FAIL("testArray is NULL!"); } 
    else { TEST_SUCCESS(); }

    return testArray_c;
}
#define TEST_makeArray(x) _Generic( (x), \
                                int: TEST_makeArray_i, \
                               char: TEST_makeArray_c, \
                             double: TEST_makeArray_d )()


int TEST_tests(void) {
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
}
