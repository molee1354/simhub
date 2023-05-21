#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "projectile.h"

// define environment
#define GROUND 0.
#define GRAVITY 9.81
#define PI 3.14159

// define projectile properties
#define RADIUS .1
#define COEF_RESTITUTION .77

// value calling index
#define INIT_X 0
#define INIT_Y 1
#define INIT_VX 2
#define INIT_VY 3
#define CUR_X 4
#define CUR_Y 5
#define CUR_VX 6
#define CUR_VY 7
#define TIME 8
#define NUMPARAMS 9

// functions
#define VSQUARE(vx, vy) ((vx*vx) + (vy*vy)) 

/* float inline VMAG(vx, vy){ */
/*     return sqrt( (vx*vx) + (vy*vy) ); */
/* } */


/*
Creating the projectile object
*/
float* makeProjectile( float x0, float y0, float vx0, float vy0, float init_t ) {
    float* out = (float*)malloc( sizeof(float)*NUMPARAMS );

    out[INIT_X] = x0;
    out[INIT_Y] = y0;
    out[INIT_VX] = vx0;
    out[INIT_VY] = vy0;

    out[CUR_X] = x0;
    out[CUR_Y] = y0;
    out[CUR_VX] = vx0;
    out[CUR_VY] = vy0;
    
    out[TIME] = init_t;

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

    // stopping condition
    if (proj[CUR_Y]-RADIUS < GROUND && proj[CUR_VY] < 0.) {
        puts("reached ground");

        // if the current KE is less than 10% of the initial KE -> stop
        if (VSQUARE( proj[INIT_VY], proj[INIT_VX] )*.1 > VSQUARE( proj[CUR_VY],proj[CUR_VX] )) {
            puts("small KE");
            return 1;
        } else {
            /*
             * TODO there seems to be an issue with not passing `proj` by
             * its reference, so the updates to the CUR_Y values seem to 
             * be behaving in a weird way
             */

            proj[CUR_VY] = -1*proj[CUR_VY]*COEF_RESTITUTION;
            proj[INIT_VY] = proj[CUR_VY];

            puts("bounce");
            return 0;
        }
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
    printf("%5.2f%15.3f%15.3f%15.3f%15.3f\n", proj[TIME], proj[CUR_X], proj[CUR_Y], proj[CUR_VX], proj[CUR_VY]);
}

void writeData( FILE *file, float time, float* proj ) {
    fprintf(file, "%5.2f%15.3f%15.3f%15.3f%15.3f\n", proj[TIME], proj[CUR_X], proj[CUR_Y], proj[CUR_VX], proj[CUR_VY]);
}

