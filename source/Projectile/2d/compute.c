#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "compute.h"
#include "obj.h"
#include "sim.input"

// functions
#define VSQUARE(vx, vy) ((vx*vx) + (vy*vy)) 

/*
   Creating the projectile object
   */
float* makeProjectile( float x0, float y0, float vx0, float vy0, float init_t ) {
    float* out = (float*)malloc( sizeof(float)*NUMPARAMS );

    /* the SIMINIT_* parameters are what the 
     * simulation was initialized with -> hence never change
     */
    out[SIMINIT_X] = x0;
    out[SIMINIT_Y] = y0;
    out[SIMINIT_VX] = vx0;
    out[SIMINIT_VY] = vy0;

    out[INIT_X] = x0;
    out[INIT_Y] = y0;
    out[INIT_VX] = vx0;
    out[INIT_VY] = vy0;

    out[CUR_X] = x0;
    out[CUR_Y] = y0;
    out[CUR_VX] = vx0;
    out[CUR_VY] = vy0;

    out[TIME] = init_t;
    out[SIMINIT_T] = init_t;

    return out;
}

/*
   Updating the state of the projectile
   */
void update_x( float time, float* proj ) {
    proj[CUR_X] = proj[CUR_VX]*time + proj[INIT_X];
}

void update_y( float time, float* proj ) {
    proj[CUR_Y] = -(.5)*GRAVITY*time*time + proj[INIT_VY]*time + proj[INIT_Y];
}

void update_vx( float time, float* proj ) {
    proj[CUR_VX] = proj[INIT_VX]; // no drag implementation
}

void update_vy( float time, float* proj ) {
    proj[CUR_VY] = -GRAVITY*time + proj[INIT_VY];
}

int updateState( float time, float* proj ) {
    update_x(time, proj);
    update_y(time, proj);
    update_vy(time, proj);
    update_vx(time, proj);

    //parametric velocity equation for projectile motion 
    proj[TIME] = time;

    // when projectile reaches ground
    if (proj[CUR_Y]-RADIUS < GROUND && proj[CUR_VY] < 0.) {

        // bounce case
        proj[CUR_VY] = -1.0*proj[CUR_VY] * COEF_RESTITUTION;

        // stopping condition if KE < 5% of initial KE
        if ( VSQUARE(proj[CUR_VX], proj[CUR_VY]) < 
                VSQUARE(proj[SIMINIT_VX], proj[SIMINIT_VY])*.05 ) {
            return -1;
        }
        // set the current state as the initial state
        proj[INIT_VX] = proj[CUR_VX];
        proj[INIT_VY] = proj[CUR_VY];
        proj[INIT_X] = proj[CUR_X];
        proj[INIT_Y] = GROUND+RADIUS;

        proj[SIMINIT_T] += time;
        return 1;
    }
    else return 0;
}

