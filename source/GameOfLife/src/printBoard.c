#include <stdio.h>
#include "board.h"

void printBoard( Board* board ) {
    for (int i=0; i<board->numRows; i++) {
        for (int j=0; j<board->numCols; j++) {
            // printf("%d ", board->boardMatrix[i][j]);
            if (board->boardMatrix[i][j]==1) printf("■ ");
            else printf("□ ");
        }
        puts("");
    }
}
