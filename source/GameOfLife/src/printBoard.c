#include "../rules.h"
#include "gol_commonincl.h"

void printBoard( Board* board ) {
    for (int i=0; i<board->numRows; i++) {
        for (int j=0; j<board->numCols; j++) {
            if (board->boardMatrix[i][j]==1) printf("■ ");
            else printf("□ ");
        }
        puts("");
    }
}
