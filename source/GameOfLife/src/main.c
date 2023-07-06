#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#include "gameOfLife.h"


int main() {

    Board* board = makeRandomBoard(NROWS, NCOLS);
    void (*nextBoard)(Board*);

    if (NCOLS > 512 && NROWS <=512) {
        puts("using openmp.");
        nextBoard = generateNext_mp;
    } else if (NCOLS > 512 && NROWS > 512) {
        puts("using nested openmp.");
        nextBoard = generateNext_mp2;
    } else {
        nextBoard = generateNext;
    }

    FILE *out;
    out = fopen(DATA_OUT, "w");
    if (out == NULL) {
        puts("File error");
        exit(1);
    }

    double start = omp_get_wtime();
    for (int i = 0; i<SIM_END; i++) {
        nextBoard(board);
        writeBoard(out, board, i);
        printf("\t%d\n", i);
        // printBoard(board);
        // puts("");
        // sleep(1);
        // system("clear");
    }
    clock_t end = omp_get_wtime();
    double elapse_time = end-start;

    printf("\nElapsed time %.3f sec\n", elapse_time);
    printf("\nFinished running GameOfLife simulation for %d timesteps\n\n", SIM_END);
    freeBoard(board);
    fclose(out);

    return 0;
}
