#include <stdio.h>
#include <unistd.h>

#include "compute.h"
#include "obj.h"
#include "sim.input"

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

