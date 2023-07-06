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


    double start = omp_get_wtime();
    for (int i = 0; i<SIM_END; i++) {
        FILE *out;
        char filename[32];
        snprintf(filename, sizeof(filename), "dumps/dump_%d.out", i);
        out = fopen(filename, "w");
        if (out == NULL) {
            puts("File error");
            exit(1);
        }

        nextBoard(board);
        writeBoard(out, board, i);
        printf("\t%d\n", i);

        fclose(out);
    }
    clock_t end = omp_get_wtime();
    double elapse_time = end-start;

    printf("\nElapsed time %.3f sec\n", elapse_time);
    printf("\nFinished running GameOfLife simulation for %d timesteps\n\n", SIM_END);
    freeBoard(board);

    return 0;
}
