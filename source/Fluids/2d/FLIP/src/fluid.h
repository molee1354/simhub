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
Fluid* initFluid(double density, double spacing, double particleRad,
                 int width, int height, int maxParticles);

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
void simulate(Fluid* fluid, Obstacle* obstacle, double dt, double gravity, int numIters);

/**
 * @brief Function to render the simulation
 */
void render(int argc, char* argv[]);

#endif
