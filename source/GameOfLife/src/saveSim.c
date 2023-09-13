#include <unistd.h>
#include <omp.h>
#include "gol_commonincl.h"


void saveSim() {

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

        fclose(out);
    }
    clock_t end = omp_get_wtime();
    double elapse_time = end-start;

    printf("\nFinished running GameOfLife simulation for %d timesteps in %.3f seconds\n\n", SIM_END, elapse_time);
    freeBoard(board);

}
