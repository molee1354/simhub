#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"
#include "sim.input"


Board* generateRandomBoard( int numRows, int numCols ) {
    // malloc free implemented by a separate function
    Board* out = (Board*)malloc( sizeof(Board) );
    int** boardMatrix = (int**)malloc( sizeof(int*)*numRows );
    for (int i = 0; i<numRows; i++) {
        boardMatrix[i] = (int*)malloc( sizeof(int)*numCols );
    }
        
    // generating a random seed for the random board generation
    srand( (unsigned int)time(NULL) );
    for (int i = 0; i<numRows; i++) {
        for (int j = 0; j<numCols; j++) {
            // generate 3x3 grid of living squares
            if ( ((i - (numRows/2 - 1)) * (i - (numRows/2 + 1)) <= 0) && 
                  ((j - (numRows/2 - 1)) * (j - (numRows/2 + 1)) <= 0) ){
              boardMatrix[i][j] = rand()%2;
            } else {
              boardMatrix[i][j] = 0;
            }
        }
    }

    out->numRows = numRows;
    out->numCols = numCols;
    out->boardMatrix = boardMatrix;

    return out;
}

/* int countNeighbors( Board* currentBoard, int rowIdx, int colIdx ) {
    currentBoard->boardMatrix;
} */

/* Board* generateNext( Board* currentBoard ) {
  
} */

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

void freeBoard( Board* board ) {
    for (int i=0; i<board->numRows; i++) {
        free(board->boardMatrix[i]);
    }
    free(board->boardMatrix);
    free(board);
}
