#include <time.h>
#include "gol_commonincl.h"

#define RAD_V NROWS/2
#define RAD_H NCOLS/2

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
            if ( ((i - (numRows/2 - RAD_V)) * (i - (numRows/2 + RAD_V)) <= 0) && 
                  ((j - (numCols/2 - RAD_H)) * (j - (numCols/2 + RAD_H)) <= 0) ){
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

Board* makeEmptyBoard( int numRows, int numCols ) {
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
