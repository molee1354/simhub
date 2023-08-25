#ifndef _value_h
#define _value_h

#include "common.h"

/**
 * @brief Enum to hold the different types that are supported
 *
 */
typedef enum {
    VAL_BOOL,
    VAL_NULL,
    VAL_NUMBER,
} ValueType;

/**
 * @brief Defining Value with a union for double and bool
 *
 */
typedef struct {
    ValueType type;
    union {
        bool boolean;
        double number;
    } as;
} Value;

/**
 * @brief Value type checking macros
 *
 */
#define IS_BOOL(value)   ( (value).type == VAL_BOOL )
#define IS_NULL(value)   ( (value).type == VAL_NULL )
#define IS_NUMBER(value) ( (value).type == VAL_NUMBER )

/**
 * @brief Unpacking the values into the C values
 *
 */
#define AS_BOOL(value) ( (value).as.boolean )
#define AS_NUMBER(value) ( (value).as.number )

/**
 * @brief Converting a native C value into the language
 * 
 */
#define BOOL_VAL(value)   ( (Value){VAL_BOOL, {.boolean = value}} )
#define NULL_VAL          ( (Value){VAL_NULL, {.number = 0}} )
#define NUMBER_VAL(value) ( (Value){VAL_NUMBER, {.number = value}} )

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
 * @brief Method to check if the two values are equal
 *
 */
bool valuesEqual(Value a, Value b);

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
