#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "compute.h"
#include "obj.h"
#include "sim.input"

// functions
#define VSQUARE(vx, vy, vz) ((vx*vx) + (vy*vy) + (vz*vz))
#define MV_INCR(prev, curr, p) ( (p-curr) < (p-prev) )
#define MV_DECR(prev, curr, p) ( (p-prev) < (p-curr) )

// box variables
#define BOX_X_LB     (SIM_BOX_ORIGIN_X - SIM_BOX_WIDTH)*.5
#define BOX_X_HB     (SIM_BOX_ORIGIN_X + SIM_BOX_WIDTH)*.5

#define BOX_Y_LB     SIM_BOX_ORIGIN_Y
#define BOX_Y_HB     SIM_BOX_ORIGIN_X + SIM_BOX_HEIGHT

#define BOX_Z_LB     (SIM_BOX_ORIGIN_Z - SIM_BOX_DEPTH)*.5
#define BOX_Z_HB     (SIM_BOX_ORIGIN_Z + SIM_BOX_DEPTH)*.5


/*
   Creating the projectile object
   */
float* makeProjectile( 
        float init_t,
        float x0, float y0, float z0,
        float vx0, float vy0, float vz0
        )
{
    float* out = (float*)malloc( sizeof(float)*NUMPARAMS );

    /* the SIMINIT_* parameters are what the 
     * simulation was initialized with -> hence never change
     */
    out[SIMINIT_X] = x0;
    out[SIMINIT_Y] = y0;
    out[SIMINIT_Z] = z0;

    out[SIMINIT_VX] = vx0;
    out[SIMINIT_VY] = vy0;
    out[SIMINIT_VZ] = vz0;

    out[INIT_X] = x0;
    out[INIT_Y] = y0;
    out[INIT_Z] = z0;

    out[INIT_VX] = vx0;
    out[INIT_VY] = vy0;
    out[INIT_VZ] = vz0;

    out[CUR_X] = x0;
    out[CUR_Y] = y0;
    out[CUR_Z] = z0;

    out[CUR_VX] = vx0;
    out[CUR_VY] = vy0;
    out[CUR_VZ] = vz0;

    out[PREV_VX] = vx0;
    out[PREV_VY] = vy0;
    out[PREV_VZ] = vz0;

    out[TIME] = init_t;
    out[SIMINIT_T] = init_t;

    return out;
}

/*
 *  Updating the state of the projectile
 *  --> each update_*() function stores the previous state
 *      so that dx, dy, dvy, etc may be computed 
 */
void update_x( float time, float* proj ) {
    proj[PREV_X] = proj[CUR_X];
    proj[CUR_X] = proj[CUR_VX]*time + proj[INIT_X];
}
void update_z( float time, float* proj ) {
    proj[PREV_Z] = proj[CUR_Z];
    proj[CUR_Z] = proj[CUR_VZ]*time + proj[INIT_Z];
}
void update_y( float time, float* proj ) {
    proj[PREV_Y] = proj[CUR_Y];
    proj[CUR_Y] = -(.5)*GRAVITY*time*time + proj[INIT_VY]*time + proj[INIT_Y];
}

void update_vx( float time, float* proj ) {
    proj[PREV_VX] = proj[CUR_VX];
    proj[CUR_VX] = proj[INIT_VX]; // no drag implementation
}
void update_vz( float time, float* proj ) {
    proj[PREV_VZ] = proj[CUR_VZ];
    proj[CUR_VZ] = proj[INIT_VZ]; // no drag implementation
}
void update_vy( float time, float* proj ) {
    proj[PREV_VY] = proj[CUR_VY];
    proj[CUR_VY] = -GRAVITY*time + proj[INIT_VY];
}

void initializeState( float time, float* proj ) {
        // set the current state as the initial state
        proj[INIT_X] = proj[CUR_X];
        proj[INIT_Z] = proj[CUR_Z];
        // proj[INIT_Y] = GROUND+RADIUS;
        proj[INIT_Y] = proj[CUR_Y];

        proj[INIT_VX] = proj[CUR_VX];
        proj[INIT_VZ] = proj[CUR_VZ];
        proj[INIT_VY] = proj[CUR_VY];

        proj[SIMINIT_T] += time;
}
int updateState( float time, float* proj ) {
    update_x(time, proj);
    update_y(time, proj);
    update_z(time, proj);

    update_vx(time, proj);
    update_vy(time, proj);
    update_vz(time, proj);

    // parametric velocity equation for projectile motion 
    proj[TIME] = time;

    /*
     * Since right now they are all if, else-if statements, only one of them
     * gets triggered at a single point. Ideally, we want multiple conditions
     * to be true so that "diagonal" movement is also possible .
     *      right now : only 1 component changing for motion 
     *      target : more than 1 component of motion changing
     *
     */

    // when projectile reaches ground
    if (proj[CUR_Y]-RADIUS < GROUND && 
            MV_DECR( proj[PREV_Y], proj[CUR_Y], GROUND )) {
        // stop case isn't triggered?

        // bounce case
        proj[CUR_VY] = -1.0*proj[CUR_VY] * COEF_RESTITUTION;

        // stopping condition if KE < 5% of initial KE
        if (
                VSQUARE(proj[CUR_VX], proj[CUR_VY], proj[CUR_VZ]) <
                VSQUARE(proj[SIMINIT_VX], proj[SIMINIT_VY], proj[SIMINIT_VZ])*.05
           ) {
            return -1;
        }
        initializeState(time, proj);

        return 1;
    // left wall
    } else if (proj[CUR_X]-RADIUS < BOX_X_LB &&
            MV_DECR( proj[PREV_X], proj[CUR_X], BOX_X_LB)) {

        // bounce case
        proj[CUR_VX] = -1.0*proj[CUR_VX] * COEF_RESTITUTION;

        // stopping condition if KE < 5% of initial KE
        if (
                VSQUARE(proj[CUR_VX], proj[CUR_VY], proj[CUR_VZ]) <
                VSQUARE(proj[SIMINIT_VX], proj[SIMINIT_VY], proj[SIMINIT_VZ])*.05
           ) {
            return -1;
        }
        initializeState(time, proj);

        return 1;

    // right wall
    } else if (proj[CUR_X]+RADIUS > BOX_X_HB &&
            MV_INCR( proj[PREV_X], proj[CUR_X], BOX_X_HB)) {

        // bounce case
        proj[CUR_VX] = -1.0*proj[CUR_VX] * COEF_RESTITUTION;

        // stopping condition if KE < 5% of initial KE
        if (
                VSQUARE(proj[CUR_VX], proj[CUR_VY], proj[CUR_VZ]) <
                VSQUARE(proj[SIMINIT_VX], proj[SIMINIT_VY], proj[SIMINIT_VZ])*.05
           ) {
            return -1;
        }
        initializeState(time, proj);

        return 1;

    // down wall
    } else if (proj[CUR_Z]-RADIUS < BOX_Z_LB &&
            MV_DECR( proj[PREV_Z], proj[CUR_Z], BOX_Z_LB)) {

        // bounce case
        proj[CUR_VZ] = -1.0*proj[CUR_VZ] * COEF_RESTITUTION;

        // stopping condition if KE < 5% of initial KE
        if (
                VSQUARE(proj[CUR_VX], proj[CUR_VY], proj[CUR_VZ]) <
                VSQUARE(proj[SIMINIT_VX], proj[SIMINIT_VY], proj[SIMINIT_VZ])*.05
           ) {
            return -1;
        }
        initializeState(time, proj);

        return 1;

    // up wall
    } else if (proj[CUR_Z]+RADIUS > BOX_Z_HB &&
            MV_INCR( proj[PREV_Z], proj[CUR_Z], BOX_Z_HB)) {

        // bounce case
        proj[CUR_VZ] = -1.0*proj[CUR_VZ] * COEF_RESTITUTION;

        // stopping condition if KE < 5% of initial KE
        if (
                VSQUARE(proj[CUR_VX], proj[CUR_VY], proj[CUR_VZ]) <
                VSQUARE(proj[SIMINIT_VX], proj[SIMINIT_VY], proj[SIMINIT_VZ])*.05
           ) {
            return -1;
        }
        initializeState(time, proj);

        return 1;
    }
    else return 0;
}

