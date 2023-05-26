#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "projectile.h"
#include "simparams.h"

// value calling index
#define SIMINIT_T     0

#define SIMINIT_X     1
#define SIMINIT_Y     2
#define SIMINIT_Z     3

#define SIMINIT_VX    4
#define SIMINIT_VY    5
#define SIMINIT_VZ    6

#define INIT_X        7
#define INIT_Y        8
#define INIT_Z        9

#define INIT_VX       10   
#define INIT_VY       11
#define INIT_VZ       12

#define CUR_X         13
#define CUR_Y         14
#define CUR_Z         15

#define CUR_VX        17
#define CUR_VY        18
#define CUR_VZ        19

#define PREV_X        20
#define PREV_Y        21
#define PREV_Z        22

#define PREV_VX       23
#define PREV_VY       24
#define PREV_VZ       25

#define TIME          26
#define NUMPARAMS     27

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

void printHeader( float time, float* proj ) {
    printf("\nProjectile simulation starting at time %f\n", time);

    // launch parameters
    printf("with initial launch parameters : \n");
    printf("\tInitial Position [x,y,z] : [ %.3f, %.3f, %.3f ]\n", 
            proj[INIT_X], proj[INIT_Y], proj[INIT_Z]);
    printf("\tInitial Velocity [vx,vy,vz] : [ %.3f, %.3f, %.3f ]\n", 
            proj[INIT_VX], proj[INIT_VY], proj[INIT_VZ]);

    // environmental parameters
    printf("\nenvironmental parameters : \n");
    printf("\tGravity : %f\n", GRAVITY);
    printf("\tGround altitude : %f\n", GROUND);

    // physical properties of the projectile
    printf("\nphysical parameters : \n");
    printf("\tRadius : %f\n", RADIUS);
    printf("\tCoefficient of restitution : %f\n", COEF_RESTITUTION);

    // physical boundary parameters
    printf("\nphysical boundary parameters : \n");
    printf("\tBox Origin (center of bottom face) [x,y,z]: [ %.3f, %.3f, %.3f ]\n",
            SIM_BOX_ORIGIN_X, SIM_BOX_ORIGIN_Y, SIM_BOX_ORIGIN_Z);
    
    if (SIM_BOX_OPEN) printf("\tBox type : OPEN\n");
    else printf("\tBox type : CLOSED\n");

    if (SIM_BOX_INF) printf("\tBox height : INFINITE\n");
    else {
        printf("\tBox height: %f", SIM_BOX_HEIGHT);
    }
    sleep(1);

    printf("\n\n%5s%12s%12s%12s%12s%12s%12s\n\n",
            "TIME",
            "pos x", "pos y", "pos z",
            "vel x", "vel y", "vel z");

    sleep(2);
}

void writeHeader( FILE *file, float time, float* proj ) {
    fprintf(file,"\nProjectile simulation starting at time %f\n", time);

    // launch parameters
    fprintf(file,"with initial launch parameters : \n");
    fprintf(file,"\tInitial Position [x,y,z] : [ %.3f, %.3f, %.3f ]\n", 
            proj[INIT_X], proj[INIT_Y], proj[INIT_Z]);
    fprintf(file,"\tInitial Velocity [vx,vy,vz] : [ %.3f, %.3f, %.3f ]\n", 
            proj[INIT_VX], proj[INIT_VY], proj[INIT_VZ]);

    // environmental parameters
    fprintf(file,"\nenvironmental parameters : \n");
    fprintf(file,"\tGravity : %f\n", GRAVITY);
    fprintf(file,"\tGround altitude : %f\n", GROUND);

    // physical properties of the projectile
    fprintf(file,"\nphysical parameters : \n");
    fprintf(file,"\tRadius : %f\n", RADIUS);
    fprintf(file,"\tCoefficient of restitution : %f\n", COEF_RESTITUTION);

    // physical boundary parameters
    fprintf(file,"\nphysical boundary parameters : \n");
    fprintf(file,"\tBox Origin (center of bottom face) [x,y,z]: [ %.3f, %.3f, %.3f ]\n",
            SIM_BOX_ORIGIN_X, SIM_BOX_ORIGIN_Y, SIM_BOX_ORIGIN_Z);
    
    if (SIM_BOX_OPEN) fprintf(file,"\tBox type : OPEN\n");
    else fprintf(file,"\tBox type : CLOSED\n");

    if (SIM_BOX_INF) fprintf(file,"\tBox height : INFINITE\n");
    else {
        fprintf(file,"\tBox height: %f", SIM_BOX_HEIGHT);
    }
    fprintf(file,"\n\n%5s%12s%12s%12s%12s%12s%12s\n\n",
            "TIME",
            "pos x", "pos y", "pos z",
            "vel x", "vel y", "vel z");
}

void printData( float time, float* proj ) {
        printf("%5.2f%12.4f%12.4f%12.4f%12.4f%12.4f%12.4f\n",
                proj[SIMINIT_T],
                proj[CUR_X], proj[CUR_Y], proj[CUR_Z],
                proj[CUR_VX], proj[CUR_VY], proj[CUR_VZ]);
}

void writeData( FILE *file, float time, float* proj ) {
        fprintf(file, "%5.2f%12.4f%12.4f%12.4f%12.4f%12.4f%12.4f\n",
                proj[SIMINIT_T],
                proj[CUR_X], proj[CUR_Y], proj[CUR_Z],
                proj[CUR_VX], proj[CUR_VY], proj[CUR_VZ]);
}
