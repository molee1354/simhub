#include "array_commonincl.h"


/* TODO:
 *
 * write out functions that can test the different array operations
 * and make sure they cover edge cases.
 *      -> out of index behaviors
 *      -> doing different things to an empty array
 * 
 * Also maybe make it so that methods for `stack` and `queue` data
 * structures can also be used:
 *      -> `stack`: push(), pop(), peek()
 *      -> `queue`: enqueue(), dequeue(), peek()
 *
 */


int main() {
    puts("array.h called");

    Array* this = makeArray(sizeof(int));
    append(this, 1);
    append(this, 1);
    append(this, 1);
    append(this, 1);

    Array* ones = onesArray(sizeof(double), 5);
    append(ones, 3.3);

    printArray(this);
    printArray(ones);
    freeArray(this);
    freeArray(ones);

    return 0;

}
