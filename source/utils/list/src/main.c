#include "list_commonincl.h"


/* TODO:
 *
 * write out functions that can test the different list operations
 * and make sure they cover edge cases.
 *      -> out of index behaviors
 *      -> doing different things to an empty list
 * 
 * Also maybe make it so that methods for `stack` and `queue` data
 * structures can also be used:
 *      -> `stack`: push(), pop(), peek()
 *      -> `queue`: enqueue(), dequeue(), peek()
 *
 */


int main() {
    puts("list.h called");

    List* this = makeList(sizeof(int));
    append(this, 1);
    append(this, 1);
    append(this, 1);
    append(this, 1);

    List* ones = onesList(sizeof(double), 5);
    append(ones, 3.3);

    printList(this);
    printList(ones);
    freeList(this);
    freeList(ones);

    return 0;

}
