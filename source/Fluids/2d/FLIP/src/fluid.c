#include "fluids_commonincl.h"
 
static int* initArray_i(int size, int elem);
static double* initArray_d(int size, double elem);
static CellType* initArray_t(int size, CellType type);
static float* initArray_f(int size, float elem);

Fluid* initFluid(double density, int numX, int numY, double h, double particleRad) {
    Fluid* out             = (Fluid*)malloc(sizeof(Fluid));
    out->density           = density;
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

    out->particleRad       = particleRad;
    out->pInvSpacing       = 1. / (2.2*particleRad);
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

static void updateParticleDensity(Fluid* fluid) {
    int n = fluid->numY;
    double h = fluid->h;
    double h1 = fluid->invSpacing;
    double h2 = fluid->h*.5;
    double* d = fluid->particleRho;

    for (int i = 0; i < fluid->numParticles; i++) {
        double x = fluid->particlePos[2*i];
        double y = fluid->particlePos[2*i+1];

        x = clamp(x, h, (fluid->numX - 1)*h);
        y = clamp(y, h, (fluid->numY - 1)*h);

        double x0 = floor( (x-h2) * h1 );
        double tx = ( (x-h2) - x0*h ) * h1;
        double x1 = findMin(x0+1, fluid->numX-2);

        double y0 = floor( (y-h2) * h1 );
        double ty = ( (y-h2) - y0*h ) * h1;
        double y1 = findMin(y0+1, fluid->numY-2);

        double sx = 1. - tx;
        double sy = 1. - ty;

        if (x0 < fluid->numX && y0 < fluid->numY) d[(int)x0*n + (int)y0] += sx*sy;
        if (x1 < fluid->numX && y0 < fluid->numY) d[(int)x1*n + (int)y0] += tx*sy;
        if (x1 < fluid->numX && y1 < fluid->numY) d[(int)x1*n + (int)y1] += tx*ty;
        if (x0 < fluid->numX && y1 < fluid->numY) d[(int)x0*n + (int)y1] += sx*ty;
    }
    if (fluid->particleRho0 == 0.) {
        double sum = 0.;
        int numFluidCells = 0;

        for (int i = 0; i < fluid->numCells; i++) {
            if (fluid->cellType[i] == FLUID_CELL) {
                sum += d[i];
                numFluidCells++;
            }
        }
        if (numFluidCells > 0) {
            fluid->particleRho0 = sum/numFluidCells;
        }
    }
}

static void transferVelocity(Fluid* fluid, bool toGrid, double flipRatio) {
    int n = fluid->numY;
    double h = fluid->h;
    double h1 = fluid->invSpacing;
    double h2 = fluid->h * .5;

    if (toGrid) {
        memcpy(fluid->prevU, fluid->u, sizeof(double)*fluid->numCells);
        memcpy(fluid->prevV, fluid->v, sizeof(double)*fluid->numCells);

        for (int i = 0; i < fluid->numCells; i++)
            fluid->cellType[i] = fluid->s[i] == 0. ? SOLID_CELL : AIR_CELL;

        for (int i = 0; i < fluid->numParticles; i++) {
            double x = fluid->particlePos[2*i];
            double y = fluid->particlePos[2*i + 1];
            double xi = clamp(floor(x * h1), 0, fluid->numX-1);
            double yi = clamp(floor(y * h1), 0, fluid->numY-1);
            int cellNr = (int)xi * n + (int)yi;
            if (fluid->cellType[cellNr] == AIR_CELL)
                fluid->cellType[cellNr] = FLUID_CELL;
        }
    }

    // looping over both u and v components
    for (int component = 0; component < 2; component++) {
        double dx = component == 0 ? 0. : h2;
        double dy = component == 0 ? h2 : 0.;
        
        double* f     = component == 0 ? fluid->u : fluid->v;
        double* prevF = component == 0 ? fluid->prevU : fluid->prevV;
        double* d     = component == 0 ? fluid->du : fluid->dv;

        for (int i = 0; i < fluid->numParticles; i++) {
            double x = fluid->particlePos[2*i];
            double y = fluid->particlePos[2*i + 1];

            x = clamp(x, h, (fluid->numX-1) * h);
            y = clamp(y, h, (fluid->numY-1) * h);

            double x0 = findMin( floor((x-dx)*h1), fluid->numX - 2);
            double tx = ( (x - dx) - x0*h) * h1;
            double x1 = findMin( x0+1, fluid->numX - 2);

            double y0 = findMin( floor((y-dy)*h1), fluid->numY - 2);
            double ty = ( (y - dy) - y0*h) * h1;
            double y1 = findMin( y0+1, fluid->numY - 2);

            double sx = 1. - tx;
            double sy = 1. - ty;

            double d0 = sx*sy;
            double d1 = tx*sy;
            double d2 = tx*ty;
            double d3 = sx*ty;

            int nr0 = (int)x0*n + (int)y0;
            int nr1 = (int)x1*n + (int)y0;
            int nr2 = (int)x1*n + (int)y1;
            int nr3 = (int)x0*n + (int)y1;

            if (toGrid) {
                double pv = fluid->particleVel[2*i + component];
                f[nr0] += pv*d0;
                d[nr0] += d0;
                f[nr1] += pv*d1;
                d[nr1] += d1;
                f[nr2] += pv*d2;
                d[nr2] += d2;
                f[nr3] += pv*d3;
                d[nr3] += d3;
            } else {
                int offset = component == 0 ? n : 1;

                double valid0 = fluid->cellType[nr0] != AIR_CELL || fluid->cellType[nr0 - offset] != AIR_CELL ? 1.0 : 0.0;
                double valid1 = fluid->cellType[nr1] != AIR_CELL || fluid->cellType[nr1 - offset] != AIR_CELL ? 1.0 : 0.0;
                double valid2 = fluid->cellType[nr2] != AIR_CELL || fluid->cellType[nr2 - offset] != AIR_CELL ? 1.0 : 0.0;
                double valid3 = fluid->cellType[nr3] != AIR_CELL || fluid->cellType[nr3 - offset] != AIR_CELL ? 1.0 : 0.0;

                double v = fluid->particleVel[2*i + component];
                double d = valid0*d0 + valid1*d1 + valid2*d2 + valid3*d3;

                if (d > 0.) {
                    double picV = ( valid0 * d0 * f[nr0] +
                                    valid1 * d1 * f[nr1] +
                                    valid2 * d2 * f[nr2] +
                                    valid3 * d3 * f[nr3] ) / d;
                    double corr = ( valid0 * d0 * (f[nr0] - prevF[nr0]) +
                                    valid1 * d1 * (f[nr1] - prevF[nr1]) +
                                    valid2 * d2 * (f[nr2] - prevF[nr2]) +
                                    valid3 * d3 * (f[nr3] - prevF[nr3]) ) / d;
                    double flipV = v + corr;

                    fluid->particleVel[2 * i + component] = (1.0 - flipRatio) * picV + flipRatio * flipV;
                }
            }
        }
        if (toGrid) {
            for (int i = 0; i < fluid->numCells; i++) {
                if (d[i] > 0.0) 
                    f[i] /= d[i];
            }

            // restoring solid cells
            for (int i = 0; i < fluid->numX; i++) {
                for (int j = 0; j < fluid->numY; j++) {
                    bool solid = fluid->cellType[i*n + j] == SOLID_CELL;
                    if (solid || (i > 0 && fluid->cellType[(i - 1)*n + j] == SOLID_CELL))
                        fluid->u[i*n + j] = fluid->prevU[i*n + j];
                    if (solid || (j > 0 && fluid->cellType[i*n + j - 1] == SOLID_CELL))
                        fluid->v[i*n + j] = fluid->prevV[i*n + j];
                }
            }
        }
    }
}

static void solveIncompressibility(Fluid* fluid, int numIters, double dt, bool drift) {
    memcpy(fluid->prevU, fluid->u, sizeof(double)*fluid->numCells);
    memcpy(fluid->prevV, fluid->v, sizeof(double)*fluid->numCells);

    int n = fluid->numY;
    double cp = fluid->density * fluid->h / dt;

    // REMOVE?
    for (int i = 0; i < fluid->numCells; i++) {
        double u = fluid->u[i];
        double v = fluid->v[i];
    }
    
    for (int iter = 0; iter < NUM_ITER; iter++) {
        for (int i = 1; i < fluid->numX-1; i++) {
            for (int j = 1; j < fluid->numY-1; j++) {
                if (fluid->cellType[i*n +j] != FLUID_CELL)
                    continue;

                int center = i*n + j;
                int left   = (i-1) * n+j;
                int right  = (i+1) * n+j;
                int bottom = i*n + j-1;
                int top    = i*n + j+1;
                
                double s   = fluid->s[center];
                double sx0 = fluid->s[left];
                double sx1 = fluid->s[right];
                double sy0 = fluid->s[bottom];
                double sy1 = fluid->s[top];
                s = sx0 + sx1 + sy0 + sy1;
                if (s == 0.)
                    continue;

                double div = fluid->u[right] - fluid->u[center] +
                             fluid->v[top] - fluid->v[center];
                if (fluid->particleRho0 > 0. && drift == 1) {
                    double k = 1.;
                    double compression = fluid->particleRho[i*n + j] - fluid->particleRho0;
                    if (compression > 0.)
                        div = div - k*compression;
                }

                double p = -div/s;
                p *= OVER_RELAX;
                fluid->p[center] +=  cp * p;
                fluid->u[center] -= sx0 * p;
                fluid->u[right]  += sx1 * p;
                fluid->v[center] -= sy0 * p;
                fluid->v[top]    += sy1 * p;
            }
        }
    }
}

static void updateParticleColors(Fluid* fluid) {
    double h1 = fluid->invSpacing;
    for (int i = 0; i < fluid->numParticles; i++) {
        double s = .01;
        fluid->particleColor[3*i]     = (float)clamp( fluid->particleColor[3*i]-s,
                                               0., 1.);
        fluid->particleColor[3*i + 1] = (float)clamp( fluid->particleColor[3*i + 1]-s,
                                               0., 1.);
        fluid->particleColor[3*i + 2] = (float)clamp( fluid->particleColor[3*i + 2]-s,
                                               0., 1.);
        double x = fluid->particlePos[2*i];
        double y = fluid->particlePos[2*i + 1];
        double xi = clamp( floor(x*h1), 1, fluid->numX-1 );
        double yi = clamp( floor(y*h1), 1, fluid->numY-1 );
        int cellNr = (int)xi + fluid->numY + (int)yi;

        double d0 = fluid->particleRho0;

        if (d0 > 0.) {
            double relativeRho = fluid->particleRho[cellNr] / d0;
            if (relativeRho < 0.7) {
                double s = 0.8;
                fluid->particleColor[3*i] = (float)s;
                fluid->particleColor[3*i+1] = (float)s;
                fluid->particleColor[3*i+2] = (float)1.;
            }
        }
    }
}

static void setSciColor(Fluid* fluid, int cellNr, double value,
                        double minVal,
                        double maxVal) {
    value = findMin(findMax(value, minVal), maxVal - .0001);
    double d = maxVal - minVal;
    value = d == 0. ? .5 : (value - minVal) / d;

    double m = .25;
    int num = (int)floor(value/m);
    float s = (value - num*m) / m;
    float red, green, blue;
    switch (num) {
        case 0: {
            red   = 0.0f;
            green = s;
            blue  = 1.0f;
            break;
        }
        case 1: {
            red   = 0.0f;
            green = 1.0f;
            blue  = 1.0f - s;
            break;
        }
        case 2: {
            red   = s;
            green = 1.0f;
            blue  = 0.0f;
            break;
        }
        case 3: {
            red   = 1.0f;
            green = 1.0f - s;
            blue  = 0.0f;
            break;
        }
    }
    fluid->cellColor[3*cellNr] = red;
    fluid->cellColor[3*cellNr+1] = green;
    fluid->cellColor[3*cellNr+2] = blue;
}

static void updateCellColors(Fluid* fluid) {
    for (int i = 0; i < fluid->numCells; i++) {
        if (fluid->cellType[i] == SOLID_CELL) {
            fluid->cellColor[3*i] = 0.5f;
            fluid->cellColor[3*i+1] = 0.5f;
            fluid->cellColor[3*i+2] = 0.5f;
        } else if (fluid->cellType[i] == FLUID_CELL) {
            double rho = fluid->particleRho[i];
            if (fluid->particleRho0 > 0.)
                rho /= fluid->particleRho0;
            setSciColor(fluid, i, rho, 0.0, 2.0);
        }
    }
}

void initialState(Fluid* fluid) {
    int n = fluid->numY;
    for (int i = 0; i < fluid->numX; i++) {
        for (int j = 0; j < fluid->numY; j++) {
            double s = 1.; // fluid
            
            // setting boundaries
            if (
                    i == 0 ||             // left bound
                    // i == fluid->numX-1 || // right bound
                    j == 0 ||             // top bound
                    j == fluid->numY-1    // bottom bound
                ) {
                s = 0.; // solid
            }
        }
    }
}

void simulate(Fluid* fluid, Obstacle* obstacle, double dt, double gravity, int numIters) {
    double substeps = 1;
    double dt_sub = dt/substeps;

    for (int step = 0; step < substeps; step++) {
        fluid->p = initArray_d(fluid->numCells, 0.);

        integrate(fluid, dt_sub, gravity);
        if (PARTICLES_SEP == 1) 
            pushParticles(fluid, numIters);
        handleParticleCollisions(fluid, obstacle,
                                 obstacle->x,
                                 obstacle->y,
                                 obstacle->radius);
        transferVelocity(fluid, true, 0.);
        updateParticleDensity(fluid);
        solveIncompressibility(fluid, numIters, dt_sub, DRIFT);
        transferVelocity(fluid, false, FLIP_RATIO);
    }
    updateParticleColors(fluid);
    updateCellColors(fluid);
}

static int* initArray_i(int size, int elem) {
    int* out = ALLOCATE(int, size);
    for (int i = 0; i < size; i++) {
        out[i] = elem;
    }
    return out;
}

static double* initArray_d(int size, double elem) {
    double* out = ALLOCATE(double, size);
    for (int i = 0; i < size; i++) {
        out[i] = elem;
    }
    return out;
}

static CellType* initArray_t(int size, CellType elem) {
    CellType* out = ALLOCATE(CellType, size);
    for (int i = 0; i < size; i++) {
        out[i] = elem;
    }
    return out;
}

static float* initArray_f(int size, float elem) {
    float* out = ALLOCATE(float, size);
    for (int i = 0; i < size; i++) {
        out[i] = elem;
    }
    return out;
}

