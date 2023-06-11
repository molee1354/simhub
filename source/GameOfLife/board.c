#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"
#include "sim.input"


/*
Matrix* makeMatrix( int row, int col, float** matPointer ) {

    Matrix* out = (Matrix*)malloc(sizeof(Matrix*));
    out->elements = matPointer;
    out->matSize[0] = row;
    out->matSize[1] = col;
    out->rows = row;
    out->cols = col;

    return out;
}

typedef struct Board {
    int** boardMatrix;
    const int numRows;
    const int numCols;
} Board;

*/
Board* generateRandomBoard( int numRows, int numCols ) {
    // make sure to malloc out these pointers well
    Board* out = (Board*)malloc( sizeof(Board*) );
    int** boardMatrix = (int**)malloc( sizeof(int*)*numRows );
    for (int i = 0; i<numCols; i++) {
        boardMatrix[i] = (int*)malloc( sizeof(int*)*numCols )
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

int countNeighbors( int rowIdx, int colIdx, Board* currentBoard ) {
  currentBoard->boardMatrix
}

Board* generateNext( Board* currentBoard ) {
  
}

void printBoard( Board* board ) {
  
}