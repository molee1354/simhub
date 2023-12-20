#ifdef NAME_MANGLE
#include "array_array.h"
#else
#include "array.h"
#endif

int main(int argc, char** argv) {
    array_int* array = makeArray_int(5);
    printArray(array);
    append(array, 15);
    printArray(array);
    freeArray(array);
    return 0;
}
