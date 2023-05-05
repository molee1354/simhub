#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "projectile.h"

int main() {

    // set initial values
    float init_x = 0.;
    float init_y = 0.;
    float init_vx = 10.0;
    float init_vy = 70.0;

    // output file
    FILE *out;
    out = fopen( "./dump", "w" );

    if (out == NULL) {
        puts("File error!");
        exit(1);
    }

    float end = 100.;
    float t = 0.;
    float increment = .01;
    float freq = .5;
    int i = 0;

    // create the projectile array
    float* proj = makeProjectile( init_x, init_y, init_vx, init_vy, t );

    printHeader(t, proj);
    writeHeader(out, t, proj);
    int state;
    while ( t < end ) {

        // if updateState() returns 1, the projectile reached the ground
        state = updateState(t, proj); 
        if ( state ) {
            printData(t, proj);
            writeData(out, t, proj);
            break;
        }

        // print data at each frequency
        if ( i == (int)(freq/increment) ) {
            printData(t, proj);
            writeData(out, t, proj);
            t += increment;
            i = 0;
            continue;
        }

        // write data for all increments
        writeData(out, t, proj);
        t += increment;
        i++;
    }

    fclose(out);
    free(proj);
    puts("\nSIM EXIT");
    return 0;
}
