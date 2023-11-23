#include "c_array_commonincl.h"
#include <stdio.h>

void* resize(void* pointer, size_t newSize) {
    if (newSize == 0) {
        free(pointer);
        return NULL;
    }
    void* out = realloc(pointer, newSize);
    if (out == NULL) {
        fprintf(stderr, "Failed to reallocate memory in 'resize()'.");
        return NULL;
    }
    return out;
}
