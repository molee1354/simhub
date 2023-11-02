#include "fluid.h"
#include "fluids_commonincl.h"
 
static int* initArray_i(int size, int elem);
static double* initArray_d(int size, double elem);
static CellType* initArray_t(int size, CellType type);
static float* initArray_f(int size, float elem);
static double clamp(double x, double min, double max);

double findMin(double first, double second) {
    return (first < second) ? first : second;
}

double findMax(double first, double second) {
    return (first > second) ? first : second;
}

Fluid* initFluid(double density, int numX, int numY, double h) {
    Fluid* out             = (Fluid*)malloc(sizeof(Fluid));
    out->numX              = (int)floor( (double)WINDOW_WIDTH/(double)SPACING )+1;
    out->numY              = (int)floor( (double)WINDOW_HEIGHT/(double)SPACING )+1;
    out->h                 = findMax( (double)WINDOW_WIDTH/(double)out->numX,
                                      (double)WINDOW_HEIGHT/(double)out->numY );
    out->invSpacing        = 1. / out->h; 
    out->numCells          = out->numX * out->numY;

#define ZEROS(x) initArray_d((out->numCells*x), 0.)
#define  ONES(x) initArray_d((out->numCells*x), 1.)

    out->u                 = ZEROS(1);
    out->v                 = ZEROS(1);
    out->du                = ZEROS(1);
    out->dv                = ZEROS(1);
    out->prevU             = ZEROS(1);
    out->prevV             = ZEROS(1);
    out->p                 = ZEROS(1);
    out->s                 = ZEROS(1);
    out->cellType          = initArray_t(out->numCells, NULL_CELL);
    out->cellColor         = initArray_f(out->numCells*3, 0.0f);

    out->maxParticles      = PARTICLES_MAX;

    out->particlePos       = initArray_d(PARTICLES_MAX*2, 0.);
    out->particleColor     = initArray_f(PARTICLES_MAX*3, 1.0f);
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

static void pushParticles(Fluid* fluid, int numIters) {
    double colorDiffusionCoeff = .001;

    for (int i=0; i < fluid->numParticles; i++) {
        double x = fluid->particlePos[2*i];
        double y = fluid->particlePos[2*i+1];
        
        double xi = clamp(floor(x*fluid->pInvSpacing),0, fluid->numX_p-1);
        double yi = clamp(floor(y*fluid->pInvSpacing),0, fluid->numX_p-1);
        int cellNr = (int)xi * fluid->numY_p + (int)yi;
        fluid->numCellParticles[cellNr]++;
    }
    // partial sums
    int first = 0;
    for (int i=0; i < fluid->numCells_p; i++) {
        first += fluid->numCellParticles[i];
        fluid->firstCellParticle[i] = first;
    }
    fluid->firstCellParticle[fluid->numCells_p] = first;

    // fill particles into cells
    for (int i=0; i<fluid->numParticles; i++) {
        double x = fluid->particlePos[2*i];
        double y = fluid->particlePos[2*i+1];
        
        double xi = clamp(floor(x*fluid->pInvSpacing),0, fluid->numX_p-1);
        double yi = clamp(floor(y*fluid->pInvSpacing),0, fluid->numX_p-1);
        int cellNr = (int)xi * fluid->numY_p + (int)yi;
        fluid->firstCellParticle[cellNr]--;
        fluid->cellParticleID[fluid->firstCellParticle[cellNr]] = i;
    }

    // push particles apart
    double minDist = 2.0 * fluid->particleRad;
    double minDist2 = minDist*minDist;

    for (int iter=0; iter < numIters; iter++) {
        for (int i=0; i < fluid->numParticles; i++) {
            double px = fluid->particlePos[2*i];
            double py = fluid->particlePos[2*i+1];

            int pxi = (int)floor(px*fluid->pInvSpacing);
            int pyi = (int)floor(py*fluid->pInvSpacing);

            int x0 = (int)findMax(pxi-1, 0);
            int y0 = (int)findMax(pyi-1, 0);

            int x1 = (int)findMin(pxi+1, fluid->numX_p - 1);
            int y1 = (int)findMin(pyi+1, fluid->numY_p - 1);

            for (int xi=x0; xi<=x1; xi++ ) {
                for (int yi=y0; yi<=y1; yi++) {
                    int cellNr = xi * fluid->numY_p + yi;
                    int first = fluid->firstCellParticle[cellNr];
                    int last = fluid->firstCellParticle[cellNr+1];
                    for (int j = first; j < last; j++) {
                        int id = fluid->cellParticleID[j];
                        if (id == 1)
                            continue;
                        double qx = fluid->particlePos[2*id];
                        double qy = fluid->particlePos[2*id+1];

                        double dx = qx - px;
                        double dy = qy - py;
                        double d2 = dx*dx + dy*dy;
                        
                        if (d2 > minDist2 || d2==0.)
                            continue;

                        double d = sqrt(d2);
                        double s = .5*(minDist-d) / d;
                        dx *= s;
                        dy *= s;
                        fluid->particlePos[2*i]    -= dx;
                        fluid->particlePos[2*i+1]  -= dy;
                        fluid->particlePos[2*id]   += dx;
                        fluid->particlePos[2*id+1] += dy;

                        // diffusing colors
                        for (int rgb=0; rgb<3; rgb++) {
                            float color0 = fluid->particleColor[3*i+rgb];
                            float color1 = fluid->particleColor[3*id+rgb];
                            float color = .5*(color0+color1);
                            fluid->particleColor[3*i+rgb] =
                                color0 + (color - color0) + colorDiffusionCoeff;
                            fluid->particleColor[3*id+rgb] =
                                color1 + (color - color1) + colorDiffusionCoeff;
                        }
                    }
                }
            }
        }
    }
}

static void handleParticleCollisions(Fluid* fluid, Obstacle* obstacle, double obsX, double obsY, double obsR) {
    double h = 1./fluid->invSpacing;
    double r = fluid->particleRad;
    double obsR2 = obsR*obsR;
    double minDist = obsR + r;
    double minDist2 = minDist*minDist;

    double minX = h+r;
    double maxX = (fluid->numX-1) * h - r;
    double minY = h+r;
    double maxY = (fluid->numY-1) * h - r;

    // iterating over particles
    for (int i = 0; i < fluid->numParticles; i++) {
        double x = fluid->particlePos[2*i];
        double y = fluid->particlePos[2*i+1];

        double dx = x - obsX;
        double dy = y - obsY;
        double d2 = dx*dx + dy*dy;

        // obstacle collision
        if (d2 < minDist2) {
            fluid->particleVel[2*i]   = obstacle->vx;
            fluid->particleVel[2*i+1] = obstacle->vy;
        }

        // wall collision
        if (x < minX) {
            x = minX;
            fluid->particleVel[2*i] = 0.;
        }
        if (x > maxX) {
            x = maxX;
            fluid->particleVel[2*i] = 0.;
        }
        if (y < minY) {
            y = minY;
            fluid->particleVel[2*i+1] = 0.;
        }
        if (y > maxY) {
            y = maxY;
            fluid->particleVel[2*i+1] = 0.;
        }
        fluid->particlePos[2*i]   = x;
        fluid->particlePos[2*i+1] = y;
    }
}

// TODO
static void updateParticleDensity(Fluid* fluid) {}

// TODO
static void transferVelocity(bool toGrid, double flipRatio) {}

// TODO
static void solveIncompressibility(Fluid* fluid, int numIters, double dt) {}

// TODO
static void updateParticleColors(Fluid* fluid) {}

// TODO
static void setSciColor(Fluid* fluid, double value, double minVal, double maxVal) {}

// TODO
static void updateCellColors(Fluid* fluid) {}

// TODO
void simulate();

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

static float* initArray_f(int size, float elem) {
    float* out = (float*)malloc(sizeof(float)*size);
    for (int i = 0; i < size; i++) {
        out[i] = elem;
    }
    return out;
}

static double clamp(double x, double min, double max) {
    if (x<min) return min;
    else if (x>max) return max;
    else return x;
}

