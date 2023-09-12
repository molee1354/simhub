#include <stdio.h>
#include <unistd.h>

#include "fluid.h"
#include "sim.input"

int main(int argc, char* argv[]) {
    Fluid* fluid = initFluid(DENSITY, NUM_X, NUM_Y, DEF_H);

    for (int i = 0; i < 50; i++) {

        simulate(DT, GRAVITY, NUM_ITER);
        sleep(1);
    }
    puts("Done.!");

    return 0;
}
