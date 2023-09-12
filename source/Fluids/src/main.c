#include <stdio.h>
#include <unistd.h>

#include "fluid.h"
#include "sim.input"

int main(int argc, char* argv[]) {
    Fluid* fluid = initFluid(DENSITY, NUM_X, NUM_Y, DEF_H);

    for (int i = 0; i < 10; i++) {
        simulate(fluid, DT, GRAVITY, NUM_ITER);
        printf("iter : %d\n", i);
        sleep(1);
    }
    freeFluid(fluid);
    puts("Done.!");

    return 0;
}
