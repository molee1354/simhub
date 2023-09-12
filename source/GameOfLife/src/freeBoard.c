#include <stdlib.h>
#include "gameOfLife.h"

void freeBoard( Board* board ) {
    for (int i=0; i<board->numRows; i++) {
        free(board->boardMatrix[i]);
        board->boardMatrix[i] = NULL;
    }
    free(board->boardMatrix);
    board->boardMatrix = NULL;
    free(board);
    board = NULL;
}
