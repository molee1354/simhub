#include<stdio.h>
#include<stdlib.h>

#include "array.h"

#define TYPE int

/* TODO:
 * write out functions that can test the different array operations
 * and make sure they cover edge cases.
 */

int main() {
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
    return 0;
}
