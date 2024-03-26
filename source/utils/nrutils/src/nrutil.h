#ifndef simhub_c_array_h
#define simhub_c_array_h

#include <stdlib.h>
    
#define ALLOCATE(type, count) \
    (type*)resize( NULL, sizeof(type)*(count) )

#define FREE(pointer) \
    resize(pointer, 0)

/**
 * @brief Function to reallocate memory from oldSize to newSize
 *
 * @param pointer 
 * @param oldSize 
 * @param newSize 
 */
void* resize(void* pointer, size_t newSize);

#endif
