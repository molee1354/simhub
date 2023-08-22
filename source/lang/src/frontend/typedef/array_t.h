
#ifndef _array_t_h
#define _array_t_h

/**
 * @brief Enum to hold the possible element types for array construction
 *
 */
typedef enum {
    TokenArray,
    StatementArray
} ArrayType;

/**
 * @brief Array object is a linked list
 *
 */
typedef struct LinkedList {
    void* head;
    void* tail;
    ArrayType type;
} Array;

#endif
