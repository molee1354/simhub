#include <stdio.h>
#include <unistd.h>

#include "compute.h"
#include "obj.h"
#include "sim.input"


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

