#ifndef _value_h
#define _value_h

#include "common.h"

typedef double Value;

/**
 * @brief The dynamic array holding the constant pool of Values.
 *
 */
typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

/**
 * @brief Method to initialize the value array
 * @param array Pointer to value array
 *
 */
void initValueArray(ValueArray* array);

/**
 * @brief Method to write a value to the value array
 * @param array Pointer to value array
 * @param value Value to write
 *
 */
void writeValueArray(ValueArray* array, Value value);
    
/**
 * @brief Method to free the value array
 * @param array Pointer to value array
 *
 */
void freeValueArray(ValueArray* array);

/**
 * @brief Method to print a given value of type Value
 * @param value Value to print
 *
 */
void printValue(Value value);

#endif
