#ifndef _vm_h
#define _vm_h

#include "chunk.h"
#include "value.h"
#include "table.h"

#define STACK_MAX 256

typedef struct {
    Chunk* chunk;

    // byte pointer that points to the instruction.
    // Dereference this pointer to get instruction
    uint8_t* ip;

    Value stack[STACK_MAX];
    Value* stackTop;
    Table globals; // hash table to hold global variables
    Table strings; // every string that's created
    Obj* objects;  // vm stores the head of the objects list
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult;

extern VM vm;

/**
 * @brief VM Constructor
 *
 */
void initVM();

/**
 * @brief VM Destructor
 *
 */
void freeVM();

/**
 * @brief Interpreting the instructions in the chunk
 * @param chunk The pointer to the chunk to interpret
 *
 */
InterpretResult interpret(const char* source);

/**
 * @brief Pushing a value into the vm stack
 * @param value Value to push into the stack
 *
 */
void push(Value value);

/**
 * @brief Popping the topmost value out out of the vm stack
 * @return Value The value that was at the top of the stack
 *
 */
Value pop();

#endif
