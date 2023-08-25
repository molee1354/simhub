#include <stdio.h>

#include "memory.h"
#include "value.h"

void initValueArray(ValueArray *array) {
    array->values = NULL;
    array->capacity = 0;
    array->count = 0;
}

void writeValueArray(ValueArray *array, Value value) {
    // checking to see if array has enough capacity
    if (array->capacity < array->count+1) {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(Value,
                array->values,
                oldCapacity,
                array->capacity);
    }
    array->values[array->count] = value;
    array->count++;
}

void freeValueArray(ValueArray* array) {
    FREE_ARRAY(uint8_t, array->values, array->capacity);
    initValueArray(array); // zero out the fields so it's in an empty state
}

void printValue(Value value) {
    printf("%g", value);
}

