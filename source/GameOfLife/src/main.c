#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "sim.input"


int main() {
    Board* newBoard = generateRandomBoard(NROWS, NCOLS);

    printBoard(newBoard);

    // check with valgrind for any memory leaks
    freeBoard(newBoard);

    return 0;
}
