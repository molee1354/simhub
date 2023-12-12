#ifndef simhub_array_h
#define simhub_array_h

#include <stdlib.h>

typedef struct {
    int capacity;
    int count;
    union {
        int* Int;
        float* Float;
        double* Double;
        char* Char;
        char** String;
    } as;
} Array;

#define ALLOCATE(type, count) \
    (type*)reallocate(NULL, 0, sizeof(type)*(count) )

#define FREE(type, pointer) \
    reallocate(pointer, sizeof(type), 0);

#define GROW_CAPACITY( capacity ) \
    ( (capacity) < 8 ? 8 : (capacity)*2 )

#define GROW_ARRAY(type, pointer, oldCount, newCount ) \
    (type*)reallocate(pointer, sizeof(type)*(oldCount), \
                      sizeof(type)*(newCount) )

#define FREE_ARRAY(type, pointer, oldCount ) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

Array* initArray();

void append(Array* array, int element);
void prepend(Array* arr);

void printArray(Array* array);

#endif
