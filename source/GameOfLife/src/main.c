#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "board.h"


int main() {
    Board* board = makeRandomBoard(NROWS, NCOLS);

    FILE *out;
    out = fopen(DATA_OUT, "w");
    if (out == NULL) {
        puts("File error");
        exit(1);
    }

    for (int i = 0; i<SIM_END; i++) {
        generateNext(board);
        writeBoard(out, board, i);
        // printBoard(board);
        // puts("");
        // sleep(1);
        // system("clear");
    }

    freeBoard(board);
    fclose(out);

    return 0;
}
