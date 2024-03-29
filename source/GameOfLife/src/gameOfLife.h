#ifndef _gameOfLife_h
#define _gameOfLife_h

#include <stdio.h>
#include <stdlib.h>
#include "sim.input"

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
Board* makeUserBoard( int** userBoard, int numRows, int numCols );

/*
 * Generates a random initial board 
 */
Board* makeRandomBoard( int numRows, int numCols );

/*
 * Generates an empty board
 */
Board* makeEmptyBoard( int numRows, int numCols );

/*
 * counting the live neighbors at a given index
 */
int countNeighbors( Board* currentBoard, int rowIdx, int colIdx );

/*
 * Take in the current board and generating the next state of the board
 */
void generateNext( Board* currentBoard );
void generateNext_mp( Board* currentBoard );
void generateNext_mp2( Board* currentBoard );

/*
 * Print current board descriptively
 */
void printBoard( Board* board );

/*
 * Write the current board to a simulation file
 */
void writeBoard( FILE* file, Board* board, int timestep );

/*
 * Freeing allocated memory
 */
void freeBoard( Board* board );
#endif

/*
 * Function to save the simulation to a dump file
 */
void saveSim();

/*
 * Function to render a live animation of the simulation
 */
void render(int argc, char* argv[]);

