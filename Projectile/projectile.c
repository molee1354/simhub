#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include "projectile.h"

// define environment
#define GROUND 0.0
#define GRAVITY 9.81

// call values by index
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

/*
Creating the projectile object
*/
float* makeProjectile( float x0, float y0, float vx0, float vy0 ) {
    float* out = (float*)malloc( sizeof(float)*NUMPARAMS );

    out[INIT_X] = x0;
    out[INIT_Y] = y0;
    out[INIT_VX] = vx0;
    out[INIT_VY] = vy0;

    out[CUR_X] = x0;
    out[CUR_Y] = y0;
    out[CUR_VX] = vx0;
    out[CUR_VY] = vy0;
    
    out[TIME] = 0;

    return out;
}

/*
Updating the state of the projectile
*/
void update_x( float time, float* proj ) {
    proj[CUR_X] = proj[CUR_VX]*time + proj[INIT_X];
}

void update_y( float time, float* proj ) {
    proj[CUR_Y] = -(1/2)*GRAVITY*time*time + proj[CUR_VY]*time + proj[INIT_Y];
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

    proj[TIME] = time;

    // stopping when the projectile hits the ground
    if (proj[CUR_Y] < GROUND) return 1;
    else return 0;
}

void printHeader( float time, float* proj ) {
    printf("\nProjectile simulation starting at time %f\n", time);
    printf("with initial launch parameters : \n");
    printf("\tInitial Position [x,y] : [ %.3f, %.3f ]\n", proj[INIT_X], proj[INIT_Y]);
    printf("\tInitial Velocity [x,y] : [ %.3f, %.3f ]\n", proj[INIT_VX], proj[INIT_VY]);
    printf("\nand physical parameters\n");
    printf("\tGravity : %f\n", GRAVITY);
    printf("\tGround altitude : %f\n", GROUND);
    sleep(1);

    printf("\n\n%5s%15s%15s%15s%15s\n\n", "TIME", "pos x", "pos y", "vel x", "vel y");
    
}
void printData( float time, float* proj ) {
    printf("%5.2f%15.3f%15.3f%15.3f%15.3f\n", proj[TIME], proj[CUR_X], proj[CUR_Y], proj[CUR_VX], proj[CUR_VY]);
}