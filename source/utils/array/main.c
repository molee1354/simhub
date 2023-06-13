#include<stdio.h>
#include<stdlib.h>

#include "array.h"
#include "test.h"


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
    int i;
    double j;
    char k;
    TEST_makeArray(i);
    TEST_makeArray(j);
    TEST_makeArray(k);
    printf("[RESULT] : %d ouf of %d tests successful.\n\n", testSuccess, testSuccess+testFail);
    return 0;
}
