#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "projectile.h"
#include "simparams.h"

// value calling index
#define SIMINIT_T     0
#define SIMINIT_X     1
#define SIMINIT_Y     2
#define SIMINIT_VX    3
#define SIMINIT_VY    4
#define INIT_X     5
#define INIT_Y     6
#define INIT_VX    7
#define INIT_VY    8
#define CUR_X      9
#define CUR_Y      10
#define CUR_VX     11
#define CUR_VY     12
#define TIME       13
#define NUMPARAMS  14

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

        // stopping condition
        if ( VSQUARE(proj[CUR_VX], proj[CUR_VY]) < 
                VSQUARE(proj[SIMINIT_VX], proj[SIMINIT_VY])*.05 ) {
            return -1;
        }
        // set the current state as the initial state
        proj[INIT_VY] = proj[CUR_VY];
        proj[INIT_VX] = proj[CUR_VX];
        proj[INIT_X] = proj[CUR_X];

        proj[SIMINIT_T] += time;
        return 1;
    }
    else return 0;
}

void printHeader( float time, float* proj ) {
    printf("\nProjectile simulation starting at time %f\n", time);

    // launch parameters
    printf("with initial launch parameters : \n");
    printf("\tInitial Position [x,y] : [ %.3f, %.3f ]\n", proj[INIT_X], proj[INIT_Y]);
    printf("\tInitial Velocity [x,y] : [ %.3f, %.3f ]\n", proj[INIT_VX], proj[INIT_VY]);

    // environmental parameters
    printf("\nenvironmental parameters : \n");
    printf("\tGravity : %f\n", GRAVITY);
    printf("\tGround altitude : %f\n", GROUND);

    // physical properties of the projectile
    printf("\nphysical parameters : \n");
    printf("\tRadius : %f\n", RADIUS);
    printf("\tCoefficient of restitution : %f\n", COEF_RESTITUTION);

    sleep(1);

    printf("\n\n%5s%15s%15s%15s%15s\n\n", "TIME", "pos x", "pos y", "vel x", "vel y");

}

void writeHeader( FILE *file, float time, float* proj ) {
    fprintf(file, "\nProjectile simulation starting at time %f\n", time);

    // launch parameters
    fprintf(file, "with initial launch parameters : \n");
    fprintf(file, "\tInitial Position [x,y] : [ %.3f, %.3f ]\n", proj[INIT_X], proj[INIT_Y]);
    fprintf(file, "\tInitial Velocity [x,y] : [ %.3f, %.3f ]\n", proj[INIT_VX], proj[INIT_VY]);

    // environmental parameters
    fprintf(file, "\nenvironmental parameters : \n");
    fprintf(file, "\tGravity : %f\n", GRAVITY);
    fprintf(file, "\tGround altitude : %f\n", GROUND);

    // physical properties of the projectile
    fprintf(file, "\nphysical parameters : \n");
    fprintf(file, "\tRadius : %f\n", RADIUS);
    fprintf(file, "\tCoefficient of restitution : %f\n", COEF_RESTITUTION);
    fprintf(file, "\n\n%5s%15s%15s%15s%15s\n\n", "TIME", "pos x", "pos y", "vel x", "vel y");
}

void printData( float time, float* proj ) {
        printf("%5.2f%15.3f%15.3f%15.3f%15.3f\n",
                proj[SIMINIT_T], proj[CUR_X], proj[CUR_Y], proj[CUR_VX], proj[CUR_VY]);
}

void writeData( FILE *file, float time, float* proj ) {
        fprintf(file, "%5.2f%15.3f%15.3f%15.3f%15.3f\n",
                proj[SIMINIT_T], proj[CUR_X], proj[CUR_Y], proj[CUR_VX], proj[CUR_VY]);
}

