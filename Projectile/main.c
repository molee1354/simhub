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
    float end = 100.;
    float t = 0.;
    float freq = 5.; // stdout print frequency

    FILE *out;
    out = fopen("./dump", "w");
    if (out == NULL) {
        puts("File error");
        exit(1);
    }

    float* proj = makeProjectile( init_x, init_y, init_vx, init_vy, t );

    printHeader(t, proj);

    // recording initial data
    printData(t, proj);
    writeData(out, t, proj);
    while ( t < end ) {
        if ( updateState(t, proj) ) {
            printData(t, proj);
            writeData(out, t, proj);
            return 0;
        } else {
            writeData(out, t, proj);
            if ( fmod(t, freq) == 0. ) printData(t, proj);

            t += 0.01;
        }
    }

    free(proj);
    fclose(out);
    return 0;
}
