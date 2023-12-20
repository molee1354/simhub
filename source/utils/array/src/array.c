#include "array_commonincl.h"
#include <stdlib.h>

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

array_int* makeArray_int(int size) {
    array_int* out = (array_int*)malloc(sizeof(array_int));
    out->capacity = size;
    out->count = size;
    out->values = (int*)calloc(size, sizeof(int));
    return out;
}

array_float* makeArray_float(int size) {
    array_float* out = (array_float*)malloc(sizeof(array_float));
    out->capacity = size;
    out->count = size;
    out->values = (float*)calloc(size, sizeof(float));
    return out;
}

array_double* makeArray_double(int size) {
    array_double* out = (array_double*)malloc(sizeof(array_double));
    out->capacity = size;
    out->count = size;
    out->values = (double*)calloc(size, sizeof(double));
    return out;
}

array_char* makeArray_char(int size) {
    array_char* out = (array_char*)malloc(sizeof(array_char));
    out->capacity = size;
    out->count = size;
    out->values = (char*)calloc(size, sizeof(char));
    return out;
}

void append_int(array_int* array, int value) {
    if (array->capacity < array->count+1) {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(int,
                                   array->values,
                                   oldCapacity,
                                   array->capacity);
    }
    array->values[array->count] = value;
    array->count++;
}

void append_float(array_float* array, int value) {
    if (array->capacity < array->count+1) {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(float,
                                   array->values,
                                   oldCapacity,
                                   array->capacity);
    }
    array->values[array->count] = value;
    array->count++;
}

void append_double(array_double* array, double value) {
    if (array->capacity < array->count+1) {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(double,
                                   array->values,
                                   oldCapacity,
                                   array->capacity);
    }
    array->values[array->count] = value;
    array->count++;
}

void append_char(array_char* array, char value) {
    if (array->capacity < array->count+1) {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(char,
                                   array->values,
                                   oldCapacity,
                                   array->capacity);
    }
    array->values[array->count] = value;
    array->count++;
}

void print_int(array_int* array) {
    printf("[");
    for (int i = 0; i < array->count-1; i++) {
        printf("%d, ", array->values[i]);
    }
    printf("%d]\n", array->values[array->count-1]);
}

void print_float(array_float* array) {
    printf("[");
    for (int i = 0; i < array->count-1; i++) {
        printf("%g, ", array->values[i]);
    }
    printf("%g]\n", array->values[array->count-1]);
}

void print_double(array_double* array) {
    printf("[");
    for (int i = 0; i < array->count-1; i++) {
        printf("%g, ", array->values[i]);
    }
    printf("%g]\n", array->values[array->count-1]);
}

void print_char(array_char* array) {
    printf("[");
    for (int i = 0; i < array->count-1; i++) {
        printf("%c, ", array->values[i]);
    }
    printf("%c]\n", array->values[array->count-1]);
}
