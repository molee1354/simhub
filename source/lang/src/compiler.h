#ifndef _compiler_h
#define _compiler_h

#include "object.h"
#include "vm.h"

/**
 * @brief Method to compile source code
 *
 * @param source Source code from input stream
 * @param chunk Chunk to write to
 * @return True if the parser encountered an error
 */
bool compile(const char* source, Chunk* chunk);

#endif
