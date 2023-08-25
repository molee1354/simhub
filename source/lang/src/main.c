#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argv[]) {
    // init vm
    initVM();

    // init chunk
    Chunk chunk;
    initChunk(&chunk);

    // add constant 1
    int constant = addConstant(&chunk, 1.3);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    // add constant 2
    int constant1 = addConstant(&chunk, 8.15);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant1, 123);

    // write return to chunk
    writeChunk(&chunk, OP_RETURN, 124);

    // show debug information about bytecode
    disassembleChunk(&chunk, "test chunk");

    // vm interpret chunk
    interpret(&chunk);

    // free objects
    freeVM();
    freeChunk(&chunk);

    return 0;
}
