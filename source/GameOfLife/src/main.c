#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "board.h"


int main() {
    Board* board = makeRandomBoard(NROWS, NCOLS);

    for (int i = 0; i<20; i++) {
        generateNext(board);
        printBoard(board);
        sleep(1);
        system("clear");
    }

    freeBoard(board);

    return 0;
}
