#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "compute.h"
#include "sim.input" 

/*
 * TODO -> make it so that simulation parameters can be defined in 
 *      a single, simulation file.
 */
int main() {
    // setting initial values
    float init_x = START_X_POS;
    float init_y = START_Y_POS;
    float init_z = START_Z_POS;
    float init_vx = START_X_VEL;
    float init_vy = START_Y_VEL;
    float init_vz = START_Z_VEL;

    int counter = SIM_START;
    int end = SIM_END;
    int freq = SIM_FREQ; // stdout print frequency
    float t = SIM_START_T;

    FILE *out;
    out = fopen(DATA_OUT, "w");
    if (out == NULL) {
        puts("File error");
        exit(1);
    }

    float* proj = makeProjectile(
            t,
            init_x, init_y, init_z,
            init_vx, init_vy, init_vz
            );

    printHeader(t, proj);
    writeHeader(out, t, proj);

    // recording initial data
    while ( counter < end ) {
        // bounce case
        if ( updateState(t, proj) == 1 ) {
            printData(t, proj);
            writeData(out, t, proj);
            t = 0.;
            continue;

        // continue case
        } else if ( updateState(t, proj) == 0 ){
            writeData(out, t, proj);
            if ( counter%freq == 0 ) {
                printData(t, proj);
            }
            t += 0.01;

        // end case
        } else {
            break;
        }
        counter++;
    }
    printf("\nSimulation ran with %d steps\n\n", counter);
    free(proj);
    fclose(out);
    return 0;
}
