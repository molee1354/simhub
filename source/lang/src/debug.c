#include <stdio.h>

#include "chunk.h"
#include "debug.h"

void disassembleChunk(Chunk *chunk, const char *name) {
    printf("== %s ==\n", name);

    for (int offset=0; offset < chunk->count; ) {
        offset = disassembleInstruction(chunk, offset);
    }
}

/**
 *
 *
 */
static int constantInstruction(const char* name, Chunk* chunk, int offset) {
    uint8_t constant = chunk->code[offset+1];
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");

    /* +2 to the offset since OP_CONST is two bytes: 1 for opcode and 1 for
    operand */
    return offset+2;
}
/**
 * @brief Display method for a simple instruction
 * @param name Name of the current instruction
 * @param offset The current offset
 *
 * @return static int The newly updated offset
 * 
 */
static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset+1;
}

int disassembleInstruction(Chunk *chunk, int offset) {
    printf("%04d ", offset);
    if (offset > 0 &&
        chunk->lines[offset] == chunk->lines[offset-1]) {
        printf("   | ");
    } else {
        printf("%4d ", chunk->lines[offset]);
    }

    uint8_t instruction = chunk->code[offset];

    switch (instruction) {
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset+1;
    }
}

