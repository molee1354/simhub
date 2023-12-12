#include "array_commonincl.h"


void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
    if (newSize > oldSize) {
    }

    if (newSize == 0) {
        free(pointer);
        return NULL;
    }

    void* result = realloc(pointer, newSize);
    if (result == NULL) exit(1);
    return result;
}

Array* initArray() {
    Array* out = (Array*)malloc(sizeof(Array*));
    out->values = ALLOCATE(int, 0);
    return out;
}
