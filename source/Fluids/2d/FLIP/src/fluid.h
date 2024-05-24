#ifndef simhub_flip_fluid_h
#define simhub_flip_fluid_h

#include "sim.input"
#include "stdio.h"
#include "stdlib.h"

typedef double* vector;

#define VECTOR_SIZE_BYTE (size_t)(sizeof(unsigned int) * 1)

#define CHECK(p)                                                               \
    if (!p) {                                                                  \
        fprintf(stderr, "vector allocate error...");                           \
        exit(EXIT_FAILURE);                                                    \
    }

#define LENGTH(vec)                                                            \
    ((int)(*((unsigned int*)(((char*)(vec)-VECTOR_SIZE_BYTE)) + 0)))

#define INIT_VECTOR(mem, out, size)                                            \
    do {                                                                       \
        *(((unsigned int*)mem) + 0) = size;                                    \
        out = (vector)((char*)mem + VECTOR_SIZE_BYTE);                         \
    } while (0)

static vector new_vector(unsigned int size) {
    void* vec_mem = calloc(1, (size) * sizeof(double) + VECTOR_SIZE_BYTE);
    CHECK(vec_mem);
    vector out;
    INIT_VECTOR(vec_mem, out, size);
    return out;
}

static void print_vector(vector vec) {
    const int size = (int)LENGTH(vec);
    printf("[");
    for (int i = 0; i < size; i++) {
        i != size ? printf("%g, ", vec[i]) : printf("%g", vec[i]);
    }
    printf("]\n");
}

static void free_vector(vector vec) {
    void* vec_mem = (void*)((char*)vec - VECTOR_SIZE_BYTE);
    free(vec_mem);
    vec_mem = NULL;
}

/* Name mangling */
#ifdef NAME_MANGLE
#include "FLIP_obstacle.h"
#else
#include "obstacle.h"
#endif

/*
 * @brief Enum to show cell type
 *
 */
typedef enum { NULL_CELL, FLUID_CELL, AIR_CELL, SOLID_CELL } CellType;

#define NULL_CELL (double)0.
#define FLUID_CELL (double)1.
#define AIR_CELL (double)2.
#define SOLID_CELL (double)3.

/*
 * @brief Struct to hold the fluid properties
 *
 */
typedef struct {
    double density;
    int fNumX;
    int fNumY;
    double h;           // side length
    double fInvSpacing; // overh
    int fNumCells;

    vector u;
    vector v;
    vector du;
    vector dv;
    vector prevU;
    vector prevV;
    vector p;
    vector s;
    vector cellType;
    vector cellColor;

    // Particles
    int maxParticles;
    vector particlePos;
    vector particleColor;
    vector particleVel;
    vector particleDensity;
    double particleRestDensity;

    double particleRadius;
    double pInvSpacing;
    int pNumX;
    int pNumY;
    int pNumCells;

    vector numCellParticles;  // int
    vector firstCellParticle; // int
    vector cellParticleIds;

    int numParticles;
} Fluid;

/**
 * @brief Utility function to find the scaled X distance between a cell index
 * and a set X position
 *
 * @param index Vertical cell index
 * @param scaleH Scale height
 * @param setX Set X position
 * @return double The scaled distance value
 */
double xDistConv(double index, double scaleH, double setX);

/**
 * @brief Utility function to find the scaled Y distance between a cell index
 * and a set Y position
 *
 * @param index Vertical cell index
 * @param scaleH Scale height
 * @param setY Set Y position
 * @return double The scaled distance value
 */
double yDistConv(double index, double scaleH, double setY);

/**
 * @brief Function to initialize the fluid struct
 *
 * @param density Density of the fluid
 * @param numX Number of cells X
 * @param numY Number of cells Y
 * @param h Side length of cell
 * @param particleRad Particle radius
 * @return Fluid* Pointer to new fluid struct
 */
Fluid* initFluid(double density, double spacing, double particleRad, int width,
                 int height, int maxParticles);

/**
 * @brief Function to set the initial state of the fluid
 *
 * @param fluid Pointer to fluid object to set
 * @param inletVel Inlet velocity
 * @param inletHeight Inlet height
 */
void initialState(Fluid* fluid);

/**
 * @brief Function to free the pointer to the fluid instance
 *
 * @param fluid Pointer to fluid to free
 */
void freeFluid(Fluid* fluid);

/**
 * @brief Function to simulate the simulation
 */
void simulate(Fluid* fluid, Obstacle* obstacle, double dt, double gravity,
              int numIters);

/**
 * @brief Function to render the simulation
 */
void render(int argc, char* argv[]);

#endif
