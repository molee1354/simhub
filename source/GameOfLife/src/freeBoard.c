#include <stdlib.h>
#include "board.h"

void freeBoard( Board* board ) {
    for (int i=0; i<board->numRows; i++) {
        free(board->boardMatrix[i]);
    }
    free(board->boardMatrix);
    free(board);
}
