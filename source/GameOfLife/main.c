#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "sim.input"


int main() {
    Board* newBoard = generateRandomBoard(NROWS, NCOLS);

    printBoard(newBoard);

    freeBoard(newBoard);

    return 0;
}
