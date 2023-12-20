#ifndef simhub_collisions_particles_h
#define simhub_collisions_particles_h

#include "hashtable.h"
typedef struct {
    int length;
    double* values;
} array;

typedef struct {
    double radius;
    array* pos;
    array* prevPos;
    array* vel;

    // define matrix

    int numParticles;
    Table table;
    bool showCollisions;
    
    // init visualization stuff
    array* colors;
}
#endif
