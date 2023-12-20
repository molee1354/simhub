#ifndef simhub_array_h
#define simhub_array_h

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int capacity;
    int count;
    int* values;
} array_int;

typedef struct {
    int capacity;
    int count;
    float* values;
} array_float;

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

#define FREE_ARRAY(array) \
    free(array->values); \
    free(array);

#define freeArray(array) FREE_ARRAY(array)

/*
 * @brief Functions to create an array
 * @return array_* pointer to an array struct
 */
array_int* makeArray_int(int size);
array_float* makeArray_float(int size);
array_double* makeArray_double(int size);
array_char* makeArray_char(int size);

/**
 * @brief Functions to append to an array
 *
 * @param array Array to append to
 * @param value Value to append
 */
void append_int(array_int* array, int value);
void append_float(array_float* array, int value);
void append_double(array_double* array, double value);
void append_char(array_char* array, char value);
#define append(array, value) _Generic( (array), \
                                 array_int* : append_int, \
                               array_float* : append_float, \
                              array_double* : append_double, \
                                array_char* : append_char ) (array, value)

/**
 * @brief Functions to print the array
 *
 * @param array Array to print
 */
void print_int(array_int* array);
void print_float(array_float* array);
void print_double(array_double* array);
void print_char(array_char* array);
#define printArray(array) _Generic ( (array), \
                                 array_int* : print_int, \
                               array_float* : print_float, \
                              array_double* : print_double, \
                                array_char* : print_char ) (array)

#endif
