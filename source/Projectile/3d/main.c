#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "compute.h"
#include "sim.input" 


int main() {
    // setting initial values 
    int counter = SIM_START;
    float t = SIM_START_T;

    FILE *out;
    out = fopen(DATA_OUT, "w");
    if (out == NULL) {
        puts("File error");
        exit(1);
    }

    float* proj = makeProjectile(
            START_X_POS, START_Y_POS, START_Z_POS,
            START_X_VEL, START_Y_VEL, START_Z_VEL,
            SIM_START_T,
            );

    printHeader(t, proj);
    writeHeader(out, t, proj);

    // recording initial data
    while ( counter < SIM_END ) {
        // bounce case
        if ( updateState(t, proj) == 1 ) {
            printData(t, proj);
            writeData(out, t, proj);
            t = 0.;
            continue;

        // continue case
        } else if ( updateState(t, proj) == 0 ){
            writeData(out, t, proj);
            if ( counter%SIM_FREQ == 0 ) {
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
    printf("\nDone!\n\n");
    free(proj);
    fclose(out);
    return 0;
}
