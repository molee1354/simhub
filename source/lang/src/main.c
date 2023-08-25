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

    constant = addConstant(&chunk, 3.4);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_ADD, 123);

    constant = addConstant(&chunk, 5.6);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);


    writeChunk(&chunk, OP_DIVIDE, 123);
    writeChunk(&chunk, OP_NEGATE, 123);

    // write return to chunk
    writeChunk(&chunk, OP_RETURN, 123);

    // show debug information about bytecode
    disassembleChunk(&chunk, "test chunk");

    // vm interpret chunk
    interpret(&chunk);

    // free objects
    freeVM();
    freeChunk(&chunk);

    return 0;
}
