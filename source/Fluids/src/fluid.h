#ifndef simhub_fluid_h
#define simhub_fluid_h

/**
 * @brief Define some scene things here for now
 *
 */
#include "sim.input"

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
 * @brief Constructor to initialize the fluid
 *
 * @param density The density of the fluid
 * @param numX The number of X cells
 * @param numY The number of Y cells
 * @param h The height (TODO)
 */
Fluid* initFluid(double density, int numX, int numY, double h);

/**
 * @brief Function to free the memory allocated for the fluid struct
 *
 * @param fluid 
 */
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
