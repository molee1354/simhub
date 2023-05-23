#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "projectile.h"
#include "simparams.h"

/*
 * TODO -> make it so that simulation parameters can be defined in 
 *      a single, simulation file.
 */
int main() {
    // setting initial values
    float init_x = START_X_POS;
    float init_y = START_Y_POS;
    float init_vx = START_X_VEL;
    float init_vy = START_Y_VEL;

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

    float* proj = makeProjectile( init_x, init_y, init_vx, init_vy, t );

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

    free(proj);
    fclose(out);
    return 0;
}
