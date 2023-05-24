#ifndef _projectile_h
#define _projectile_h

#include <stdio.h>

float* makeProjectile( float x0, float y0, float vx0, float vy0, float init_t );

void update_x( float time, float* proj );
void update_y( float time, float* proj );
void update_vx( float time, float* proj );
void update_vy( float time, float* proj );
float get_ke( float v1, float v2 );

int updateState( float time, float* proj );
void printHeader( float time, float* proj );
void printData( float time, float* proj );

void writeHeader( FILE *file, float time, float* proj );
void writeData( FILE *file, float time, float* proj );

#endif
