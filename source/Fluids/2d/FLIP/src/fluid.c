#include "fluid.h"
#include "fluids_commonincl.h"
 
static int* initArray_i(int size, int elem);
static double* initArray_d(int size, double elem);
static CellType* initArray_t(int size, CellType type);
static RGB* initArray_R(int size, float color);

double findMin(double first, double second) {
    return (first < second) ? first : second;
}

double findMax(double first, double second) {
    return (first > second) ? first : second;
}

Fluid* initFluid(double density, int numX, int numY, double h) {
#define ZEROS(x) initArray_d((out->numCells*x), 0.)
#define  ONES(x) initArray_d((out->numCells*x), 1.)

    Fluid* out             = (Fluid*)malloc(sizeof(Fluid));
    out->numX              = (int)floor( (double)WINDOW_WIDTH/(double)SPACING )+1;
    out->numY              = (int)floor( (double)WINDOW_HEIGHT/(double)SPACING )+1;
    out->h                 = findMax( (double)WINDOW_WIDTH/(double)out->numX,
                                      (double)WINDOW_HEIGHT/(double)out->numY );
    out->invSpacing        = 1. / out->h; 

    out->u                 = ZEROS(1);
    out->v                 = ZEROS(1);
    out->du                = ZEROS(1);
    out->dv                = ZEROS(1);
    out->prevU             = ZEROS(1);
    out->prevV             = ZEROS(1);
    out->p                 = ZEROS(1);
    out->s                 = ZEROS(1);
    out->cellType          = initArray_t(out->numCells, NULL_CELL);
    out->cellColor         = initArray_R(out->numCells, 0.0f);

    out->maxParticles      = PARTICLES_MAX;

    out->particlePos       = initArray_d(PARTICLES_MAX*2, 0.);
    out->particleColor     = initArray_R(out->maxParticles, 1.0f);
    out->particleVel       = initArray_d(PARTICLES_MAX*2, 0.);
    out->particleRho       = ZEROS(1);
    out->particleRho0      = 0.;

    out->particleRad       = PARTICLES_RAD;
    out->pInvSpacing       = 1. / (2.2*PARTICLES_RAD);
    out->numX_p            = (int)floor(WINDOW_WIDTH * out->pInvSpacing)+1;
    out->numY_p            = (int)floor(WINDOW_HEIGHT * out->pInvSpacing)+1;
    out->numCells_p        = out->numX_p * out->numY_p;

    out->numCellParticles  = initArray_i(out->numCells_p, 0);
    out->firstCellParticle = initArray_i(out->numCells_p+1, 0);
    out->numParticles      = 0;


#undef ZEROS
#undef ONES
    return out;
}

/**
 * @brief Function to integrate the particle's position and velocity
 *
 * @param fluid Pointer to fluid
 * @param dt Delta t
 * @param gravity Gravity
 */
static void integrate(Fluid* fluid, double dt, double gravity) {
    for (int i = 0; i < fluid->numParticles; i++) {
        fluid->particleVel[2*i+1] += dt*gravity;
        fluid->particlePos[2*i] += fluid->particleVel[2*i] * dt;
        fluid->particlePos[2*i+1] += fluid->particleVel[2*i+1]*dt;
    }
}



static int* initArray_i(int size, int elem) {
    int* out = (int*)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        out[i] = elem;
    }
    return out;
}

static double* initArray_d(int size, double elem) {
    double* out = (double*)malloc(sizeof(double) * size);
    for (int i = 0; i < size; i++) {
        out[i] = elem;
    }
    return out;
}

static CellType* initArray_t(int size, CellType elem) {
    CellType* out = (CellType*)malloc(sizeof(CellType) * size);
    for (int i = 0; i < size; i++) {
        out[i] = elem;
    }
    return out;
}

static RGB* initArray_R(int size, float color) {
    RGB* out = (RGB*)malloc(sizeof(RGB)*size);
    for (int i = 0; i < size; i++) {
        out->red = color;
        out->green = color;
        out->blue = color;
    }
    return out;
}
