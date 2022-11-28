#include<stdio.h>
#include<stdlib.h>
#include "linkedlist.h"

int main() {
    List* myList = makeList();

    printf("List Length at first : %d\n",getLength(myList));
    for (int i = 10; i>0; i--) append(myList, i);

    printList(myList);
    int idx = 2;
    printf("List[%d] : %d\n", idx, getElement(myList, idx));

    printf("Index of 3 : %d\n", findIndex(myList, 3));

    free(myList);
    return 0;
}