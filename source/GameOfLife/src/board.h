#ifndef _board_h
#define _board_h

#include <stdio.h>

/*
 * Board struct to hold the size of the board / the current state
 */
typedef struct Board {
    int** boardMatrix;
    int numRows;
    int numCols;
} Board;

/*
 * Takes user input and generates the initial board
 */
Board* generateUserBoard( int** userBoard, int numRows, int numCols );

/*
 * Generates a random initial board 
 */
Board* generateRandomBoard( int numRows, int numCols );

/*
 * Generates an empty board
 */
Board* generateEmtpyBoard( int numRows, int numCols );

/*
 * counting the live neighbors at a given index
 */
int countNeighbors( Board* currentBoard, int rowIdx, int colIdx );

/*
 * Take in the current board and generating the next state of the board
 */
Board* generateNext( Board* currentBoard );

/*
 * Print current board descriptively
 */
void printBoard( Board* board );

/*
 * Write the current board to a simulation file
 */
void writeBoard( FILE* file, Board* board );

/*
 * Freeing allocated memory
 */
void freeBoard( Board* board );
#endif

// reference:
// https://github.com/noahhaasis/conwaysGameOfLife