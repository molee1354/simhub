#include <omp.h>
#include "gol_commonincl.h"


void generateNext_mp2( Board* currentBoard ) {
    Board* nextBoard = makeEmptyBoard(currentBoard->numRows, currentBoard->numCols);

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < currentBoard->numRows; i++) {
        for (int j = 0; j < currentBoard->numCols; j++) {
            int neighborCount = countNeighbors(currentBoard, i, j);
            int isAlive = currentBoard->boardMatrix[i][j];
            if (isAlive) {
                if ( neighborCount < 2 ) {nextBoard->boardMatrix[i][j] = 0;}
                if ( neighborCount == 2 || neighborCount == 3 ) {
                    nextBoard->boardMatrix[i][j] = 1;
                }
                if ( neighborCount > 3 ) {nextBoard->boardMatrix[i][j] = 0;}
            } else {
                if ( neighborCount == 3) {nextBoard->boardMatrix[i][j] = 1;}
                else {nextBoard->boardMatrix[i][j] = 0;}
            }
        }
    }

    // copying the next board into the current board
    for (int i = 0; i < currentBoard->numRows; i++) {
        for (int j = 0; j < currentBoard->numCols; j++) {
            currentBoard->boardMatrix[i][j] = nextBoard->boardMatrix[i][j];
        }
    }
    freeBoard(nextBoard);
}
