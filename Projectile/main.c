#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "projectile.h"

int main() {
    // setting initial values
    float init_x = 0.;
    float init_y = 0.;
    float init_vx = 10.0;
    float init_vy = 70.0;

    // simulation start and end parameters
    int end = 10000;
    int freq = 100; // stdout print frequency
    int counter = 0;
    float t = 0.;

    FILE *out;
    out = fopen("./dump", "w");
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
