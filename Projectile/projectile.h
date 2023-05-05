#ifndef _projectile_h
#define _projectile_h

/*
 * Defining the current state of the projectile
 */
// typedef struct Projectile {
//     // [0] -> x, [1] -> y
    
//     // initial state (const)
//     float init_pos[2];
//     float init_vel[2];

//     // current state (updated)
//     float cur_pos[2];
//     float cur_vel[2];

//     int time;
// } Projectile;

float* makeProjectile( float x0, float y0, float vx0, float vy0 );
void update_x( float time, float* proj );
void update_y( float time, float* proj );
void update_vx( float time, float* proj );
void update_vy( float time, float* proj );

int updateState( float time, float* proj );
void printHeader( float time, float* proj );
void printData( float time, float* proj );

#endif