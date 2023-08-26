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
        case OP_NULL:
            return simpleInstruction("OP_NULL", offset);
        case OP_TRUE:
            return simpleInstruction("OP_TRUE", offset);
        case OP_FALSE:
            return simpleInstruction("OP_FALSE", offset);
        case OP_POP:
            return simpleInstruction("OP_POP", offset);
        case OP_GET_GLOBAL:
            return constantInstruction("OP_GET_GLOBAL", chunk, offset);
        case OP_DEFINE_GLOBAL:
            return constantInstruction("OP_DEFINE_GLOBAL", chunk,
                                       offset);

        case OP_EQUAL:
            return simpleInstruction("OP_EQUAL", offset);
        case OP_GREATER:
            return simpleInstruction("OP_GREATER", offset);
        case OP_LESS:
            return simpleInstruction("OP_LESS", offset);

        case OP_ADD:
            return simpleInstruction("OP_ADD", offset);
        case OP_SUBTRACT:
            return simpleInstruction("OP_SUBTRACT", offset);
        case OP_MULTIPLY:
            return simpleInstruction("OP_MULTIPLY", offset);
        case OP_DIVIDE:
            return simpleInstruction("OP_DIVIDE", offset);
        case OP_MOD:
            return simpleInstruction("OP_MOD", offset);

        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);

        case OP_NOT:
            return simpleInstruction("OP_NOT", offset);
        case OP_NEGATE:
            return simpleInstruction("OP_NEGATE", offset);
        case OP_PRINT:
            return simpleInstruction("OP_PRINT", offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset+1;
    }
}

