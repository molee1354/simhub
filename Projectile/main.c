#include<stdio.h>
#include<stdlib.h>

#include "projectile.h"

int main() {
    float init_x = 0.;
    float init_y = 0.;
    float init_vx = 10.0;
    float init_vy = 70.0;

    float* proj = makeProjectile( init_x, init_y, init_vx, init_vy );

    float end = 100.;
    float t = 0.;
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
