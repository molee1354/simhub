#include "../rules.h"

#ifdef NAME_MANGLE
#include "GameOfLife_gameOfLife.h"
#else
#include "gameOfLife.h"
#endif

int countNorthWest( Board* currentBoard, int rowIdx, int colIdx ) {
    if (rowIdx <= 0 || colIdx <= 0) {
        return 0;
    } 
    return currentBoard->boardMatrix[rowIdx-1][colIdx-1];
}
int countNorthEast( Board* currentBoard, int rowIdx, int colIdx ) {
    if (rowIdx <= 0 || colIdx >= currentBoard->numCols-1) {
        return 0;
    } 
    return currentBoard->boardMatrix[rowIdx-1][colIdx+1];
}
int countNorth( Board* currentBoard, int rowIdx, int colIdx ) {
    if (rowIdx == 0) {
        return 0;
    } 
    return currentBoard->boardMatrix[rowIdx-1][colIdx+0];
}

int countSouthWest( Board* currentBoard, int rowIdx, int colIdx ) {
    if (rowIdx >= currentBoard->numRows-1 || colIdx <= 0) {
        return 0;
    } 
    return currentBoard->boardMatrix[rowIdx+1][colIdx-1];
}
int countSouthEast( Board* currentBoard, int rowIdx, int colIdx ) {
    if (rowIdx >= currentBoard->numRows-1 || colIdx >= currentBoard->numCols-1) {
        return 0;
    } 
    return currentBoard->boardMatrix[rowIdx+1][colIdx+1];
}
int countSouth( Board* currentBoard, int rowIdx, int colIdx ) {
    if (rowIdx >= currentBoard->numRows-1) {
        return 0;
    } 
    return currentBoard->boardMatrix[rowIdx+1][colIdx+0];
}
int countEast( Board* currentBoard, int rowIdx, int colIdx ) {
    if (colIdx >= currentBoard->numCols-1) {
        return 0;
    } 
    return currentBoard->boardMatrix[rowIdx+0][colIdx+1];
}
int countWest( Board* currentBoard, int rowIdx, int colIdx ) {
    if (colIdx <= 0) {
        return 0;
    } 
    return currentBoard->boardMatrix[rowIdx+0][colIdx-1];
}

int countNeighbors( Board* currentBoard, int rowIdx, int colIdx ) {
    int sum = 0;
    int (*countFs[]) (Board*, int, int) = {
        countNorthWest, countNorth, countNorthEast,
        countWest,      /* self */  countEast,
        countSouthWest, countSouth, countSouthEast
    };

    for (long unsigned int i = 0; i<sizeof(countFs)/sizeof(countFs[0]); i++) {
        sum += countFs[i] (currentBoard, rowIdx, colIdx);
    }
    return sum;
}
