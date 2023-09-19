#ifndef simhub_fluid_h
#define simhub_fluid_h

#include "deps.h"

/**
 * @brief Define some scene things here for now
 *
 */
#define OVER_RELAX 1.9

/**
 * @class Fluid
 * @brief Structure for the main fluid to simulate
 * 
 */
typedef struct {
    double density;
    int numX;
    int numY;
    int numCells;

    double h;

    double* u;
    double* v;
    double* newU;
    double* newV;

    double* p;
    double* s;
    double* m;
    double* newM;

    int num;
} Fluid;

typedef enum {
    U_FIELD,
    V_FIELD,
    S_FIELD
} FieldType;

extern double dx;
extern double dy;

/**
 * @brief Constructor to initialize the fluid
 *
 * @param density The density of the fluid
 * @param numX The number of X cells
 * @param numY The number of Y cells
 * @param h The height (TODO)
 */
Fluid* initFluid(double density, int numX, int numY, double h);

void freeFluid(Fluid* fluid);

/**
 * @brief Function to calculate the fluid simulations
 *
 * @param dt 
 * @param gravity 
 * @param numIters 
 */
void simulate(Fluid* fluid, double dt, double gravity, int numIters);

/**
 * @brief Function to render the simulation
 */
void render();

#endif
