#include <stdio.h>

#include "fluid.h"
#include "sim.input"

int main(int argc, char* argv[]) {
    initFluid(DENSITY, NUM_X, NUM_Y, DEF_H);

    simulate(DT, GRAVITY, NUM_ITER);
    puts("Done.!");

    return 0;
}
