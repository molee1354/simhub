#ifndef simhub_array_h
#define simhub_array_h

#include <stdlib.h>

typedef struct {
    int capacity;
    int count;
    int* values;
} array_int;

typedef struct {
    int capacity;
    int count;
    double* values;
} array_double;

typedef struct {
    int capacity;
    int count;
    char* values;
} array_char;

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

array_int* makeArray_int(int size);
array_double* makeArray_double(int size);
array_char* makeArray_char(int size);

#endif
