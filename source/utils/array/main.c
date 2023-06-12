#include<stdio.h>
#include<stdlib.h>

#include "array.h"

#define TYPE int

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
    // append(myArray, (TYPE)69);
    printf("Array length : %d\n", getLength( myArray ));

    puts("\ndeleteTail()");
    deleteTail( myArray );
    printf("Array length : %d\n", getLength( myArray ));
    listRepr( myArray );

    puts("\ndeleteTail()");
    deleteTail( myArray );
    printf("Array length : %d\n", getLength( myArray ));
    listRepr( myArray );

    /* puts("deleteHead()");
    deleteHead( myArray );
    printf("Array length : %d\n", getLength( myArray ));
    printArray( myArray ); */

    puts("\nfreeArray()");
    freeArray( myArray );
    return 0;
}
