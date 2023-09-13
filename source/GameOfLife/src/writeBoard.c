#include "../rules.h"

#ifdef NAME_MANGLE
#include "GameOfLife_gameOfLife.h"
#else
#include "gameOfLife.h"
#endif

void writeBoard( FILE* file, Board* board, int timestep ) {
    fprintf(file, "\nTimestep : %d\n", timestep);
    for (int i=0; i<board->numRows; i++) {
        for (int j=0; j<board->numCols; j++) {
            // printf("%d ", board->boardMatrix[i][j]);
            if (board->boardMatrix[i][j]==1) fprintf(file, "1 ");
            else fprintf(file, "0 ");
        }
        fprintf(file, "\n");
    }
}
