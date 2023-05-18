#include<stdio.h>
#include<stdlib.h>

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

    FILE *out;
    out = fopen("./dump", "w");
    if (out == NULL) {
        puts("File error");
        exit(1);
    }

    float* proj = makeProjectile( init_x, init_y, init_vx, init_vy, t );

    printHeader(t, proj);
    while ( t < end ) {
        if ( updateState(t, proj) ) {
            printData(t, proj);
            return 0;
        } else {
            printData(t, proj);
            t += 0.01;
        }
    }

    free(proj);
    return 0;
}
