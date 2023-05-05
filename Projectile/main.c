#include<stdio.h>
#include<stdlib.h>

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

    // create the projectile array
    float* proj = makeProjectile( init_x, init_y, init_vx, init_vy );

    float end = 100.;
    float t = 0.;
    printHeader(t, proj);
    writeHeader(out, t, proj);
    while ( t < end ) {

        // if updateState() returns 1, the projectile reached the ground
        if ( updateState(t, proj) ) {
            printData(t, proj);
            writeData(out, t, proj);
            break;
        }
        printData(t, proj);
        writeData(out, t, proj);
        t += 0.01;
    }

    fclose(out);
    free(proj);
    return 0;
}
