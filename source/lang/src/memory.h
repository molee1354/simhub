#ifndef _memory_h
#define _memory_h

#include "common.h"

/**
 * @brief Macro definition to double the capacity of the byte array
 *
 */
#define GROW_CAPACITY( capacity ) \
    ( (capacity) < 8 ? 8 : (capacity)*2 )

/**
 * @brief Macro definition to grow the capacity of the array
 *
 */
#define GROW_ARRAY( type, pointer, oldCount, newCount ) \
    (type*)reallocate( pointer, sizeof(type)*(oldCount), \
                       sizeof(type)*(newCount) )

/**
 * @brief Macro definition to free the dynamic array. Simply freeing 
 *  and resizing the array to a zero count. Wraps reallocate by passing
 *  in a zero as a new count.
 *
 */
#define FREE_ARRAY( type, pointer, oldCount ) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

/**
 * @brief Method to reallocate and resize memory into a given size.
 * @param pointer pointer to the memory block to resize
 * @param oldSize old size
 * @param newSize new size
 *
 * @return void* a pointer to the newly sized block.
 * Will be casted to its new type
 */
void* reallocate(void* pointer, size_t oldSize, size_t newSize);

#endif
