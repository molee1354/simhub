#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gameOfLife.h"

#define RAD 5

Board* makeRandomBoard( int numRows, int numCols ) {
    Board* out = (Board*)malloc( sizeof(Board) );
    int** boardMatrix = (int**)malloc( sizeof(int*)*numRows );
    for (int i = 0; i<numRows; i++) {
        boardMatrix[i] = (int*)malloc( sizeof(int)*numCols );
    }
        
    // generating a random seed for the random board generation
    srand( (unsigned int)time(NULL) );
    for (int i = 0; i<numRows; i++) {
        for (int j = 0; j<numCols; j++) {
            // make 3x3 grid of living squares
            if ( ((i - (numRows/2 - RAD)) * (i - (numRows/2 + RAD)) <= 0) && 
                  ((j - (numRows/2 - RAD)) * (j - (numRows/2 + RAD)) <= 0) ){
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

Board* makeUserBoard( int** userBoard, int numRows, int numCols ) {
    Board* out = (Board*)malloc( sizeof(Board) );
    out->numRows = numRows;
    out->numCols = numCols;
    out->boardMatrix = userBoard;
    return out;
}

Board* makeEmtpyBoard( int numRows, int numCols ) {
    Board* out = (Board*)malloc( sizeof(Board) );

    int** boardMatrix = (int**)calloc( numRows, sizeof(int*) );
    for (int i = 0; i<numRows; i++) {
        boardMatrix[i] = (int*)calloc( numCols, sizeof(int) );
    }
        
    out->numRows = numRows;
    out->numCols = numCols;
    out->boardMatrix = boardMatrix;

    return out;
}
