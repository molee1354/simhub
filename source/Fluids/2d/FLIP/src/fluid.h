#ifndef simhub_flip_fluid_h
#define simhub_flip_fluid_h

#include "sim.input"

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
typedef enum {
    NULL_CELL,
    FLUID_CELL,
    AIR_CELL,
    SOLID_CELL
} CellType;

/*
 * @brief Struct to hold the fluid properties
 *
 */
typedef struct {
    double density;
    int numX;
    int numY;

    double h;
    double invSpacing;

    int numCells;

    double* u;
    double* v;
    double* du;
    double* dv;
    double* prevU;
    double* prevV;
    double* p;
    double* s;
    CellType* cellType;
    float* cellColor;

    int maxParticles;
    double* particlePos;
    float* particleColor;

    double* particleVel;
    double* particleRho;
    double particleRho0;

    double particleRad;
    double pInvSpacing;

    int numX_p;
    int numY_p;
    int numCells_p;

    int* numCellParticles;
    int* firstCellParticle;
    int* cellParticleID;

    int numParticles;
} Fluid;
 
/**
 * @brief Utility function to find the minimum value between two values
 *
 * @param first 
 * @param second 
 * @return double Minimum value
 */
double findMin(double first, double second);

/**
 * @brief Utility function to find the maximum value between two values
 *
 * @param first 
 * @param second 
 * @return double Maximul value
 */
double findMax(double first, double second);

/**
 * @brief Function to initialize the fluid struct
 *
 * @param density Density of the fluid
 * @param numX Number of cells X
 * @param numY Number of cells Y
 * @param h Side length of cell
 * @return Fluid* Pointer to new fluid struct
 */
Fluid* initFluid(double density, int numX, int numY, double h);

/**
 * @brief Function to free the pointer to the fluid instance
 *
 * @param fluid Pointer to fluid to free
 */
void freeFluid(Fluid* fluid);

/**
 * @brief Function to simulate the simulation
 */
void simulate();

#endif
