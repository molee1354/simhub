#ifndef simhub_collisions_particles_h
#define simhub_collisions_particles_h

#include <stdbool.h>

#ifdef NAME_MANGLE
#include "helper_helper.h"
#include "array_array.h"
#include "collisions_hashtable.h"
#else
#include "../../utils/helper/src/helper.h"
#include "../../utils/array/src/array.h"
#include "hashtable.h"
#endif

typedef struct {
    double radius;
    array_double* pos;
    array_double* prevPos;
    array_double* vel;

    // define matrix

    int numParticles;
    Table* table;
    bool showCollisions;
    array_double* normal;
    
    // init visualization stuff
    array_float* colors;
} Particles;

Particles* initParticles(double radius, array_double* pos, array_double* vel);

void freeParticles(Particles* particles);

void updateMesh(Particles* particles);

void simulate(Particles* particles, double dt, array_double* gravity, array_int* bounds);

#endif
