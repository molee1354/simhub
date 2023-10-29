#ifndef simhub_fluid_h
#define simhub_fluid_h

/**
 * @brief Define some scene things here for now
 *
 */
#include "sim.input"

/* Name mangling */
#ifdef NAME_MANGLE
#include "FVM_obstacle.h"
#else
#include "obstacle.h"
#endif

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
 * @brief Constructor to initialize the fluid object
 *
 * @param density The density of the fluid
 * @param numX The number of X cells
 * @param numY The number of Y cells
 * @param h The height (TODO)
 */
Fluid* initFluid(double density, int numX, int numY, double h);

/**
 * @brief Function to set the initial state of the fluid
 *
 * @param fluid Pointer to fluid object to set
 * @param inletVel Inlet velocity
 * @param inletHeight Inlet height
 */
void initialState(Fluid* fluid, double inletVel, double inletHeight);

/**
 * @brief Function to free the memory allocated for the fluid struct
 *
 * @param fluid 
 */
void freeFluid(Fluid* fluid);

/**
 * @brief Function to sample the given fluid field
 *
 * @param fluid Pointer to fluid to sample
 * @param x X coordinate
 * @param y Y coordinate
 * @param field Enum of the field that will be sampled
 * @return double Velocity component of the fluid field at coordinate x,y
 */
double sampleField(Fluid* fluid, double x, double y, FieldType field);

/**
 * @brief Function to calculate the fluid simulations
 *
 * @param dt 
 * @param gravity 
 * @param numIters 
 */
void simulate(Fluid* fluid, Obstacle* obstacle, double dt, double gravity, int numIters);

/**
 * @brief Function to render the simulation
 */
void render(int argc, char* argv[]);

#endif
