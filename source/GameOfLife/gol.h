#ifndef _gol_h
#define _gol_h

int** generateUserBoard( int numRows, int numCols, int** userBoard );
int** generateRandomBoard( int numRows, int numCols );
int countNeighbors( int rowIdx, int colIdx, int** board );

#endif

// https://github.com/noahhaasis/conwaysGameOfLife
