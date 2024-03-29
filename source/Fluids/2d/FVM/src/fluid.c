#include <omp.h>
#include "fluids_commonincl.h"

static double* initArray(int size, double elem);

double xDistConv(double index, double scaleH, double setX) {
    return (index + .5) * scaleH - (DOMAIN_WIDTH/WINDOW_WIDTH)*setX;
}

double yDistConv(double index, double scaleH, double setY) {
    return (index + .5) * scaleH - (DOMAIN_HEIGHT/WINDOW_HEIGHT)*setY;
}

Fluid* initFluid(double density, int numX, int numY, double h) {
    Fluid* out = (Fluid*)malloc(sizeof(Fluid));
    if (out==NULL) {
        printf("Error: could not allocate memory for fluid struct.");
        return NULL;
    }
    out->density = density;
    out->numX = numX + 2;
    out->numY = numY + 2;
    out->numCells = out->numX * out->numY;
    printf("numcells : %d\n",out->numCells);
    out->h = h;

#define ZEROS() initArray(out->numCells, 0.)
#define  ONES() initArray(out->numCells, 1.)

    out->u = ZEROS();
    out->v = ZEROS();
    out->newU = ZEROS();
    out->newV = ZEROS();

    out->s = ZEROS();
    out->m = ONES();
    out->newM = ZEROS();

    out->num = numX * numY;

#undef ZEROS
#undef ONES
    return out;
}

void initialState(Fluid* fluid, double inletVel, double inletHeight) {
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

            fluid->s[i*n + j] = s;
            if (i == 1) {
                fluid->u[i*n + j] = inletVel;
            }
        }
    }

    double pipeHeight = inletHeight * (double)(fluid->numY);
    double minJ = (int)floor(.5 * fluid->numY - .5*pipeHeight);
    double maxJ = (int)floor(.5 * fluid->numY + .5*pipeHeight);

    for (int j = minJ; j < maxJ; j++) {
        fluid->m[j] = 0.;
    }
}

void freeFluid(Fluid* fluid) {
    FREE(fluid->u);
    FREE(fluid->v);
    FREE(fluid->s);
    FREE(fluid->m);
    FREE(fluid->newU);
    FREE(fluid->newV);
    FREE(fluid->newM);
    FREE(fluid);
}

static double* initArray(int size, double elem) {
    double* out = ALLOCATE(double, size);
    for (int i = 0; i < size; i++) {
        out[i] = elem;
    }
    return out;
}

/**
 * @brief Function to integrate with dt
 *
 * @param dt
 * @param gravity 
 */
static void integrate(Fluid* fluid, double dt, double gravity, Obstacle* obstacle) {
    int n = fluid->numY;
    double h = fluid->h;
    double obsX = (double)obstacle->x;
    double obsY = (double)obstacle->y;
    for (int i = 1; i < fluid->numX; i++) {
        for (int j = 1; j < fluid->numY-1; j++) {
            if (fluid->s[i*n + j] != 0. && fluid->s[i*n + j-1] != 0.) {
                fluid->v[i*n + j] += gravity*dt;

                // coordinate difference between current cell and obstacle
                double dx = xDistConv((double)i, h, obsX);
                double dy = yDistConv((double)j, h, obsY);
                double rad2 = (double)(obstacle->radius * obstacle->radius);

                // if current cell is right outside the obstacle boundary
                if (dx*dx + dy*dy < rad2+h && dx*dx + dy*dy > rad2-h) {
                    // Convert units from Rev/s to radians / (1/60) sec
                    // dt = 1/60
                    double vx = ( OBSTACLE_OMEGA*(2.*M_PI)*dt ) * fabs(dx);
                    double vy = ( OBSTACLE_OMEGA*(2.*M_PI)*dt ) * fabs(dy);
                    fluid->u[i*n + j]     += vx;
                    fluid->u[(i+1)*n + j] += vx;
                    fluid->v[i*n + j]     += vy;
                    fluid->v[i*n + j+1]   += vy;
                }
            }
        }
    }
}

static void solveIncompress(Fluid* fluid, int numIters, double dt) {
    int n = fluid->numY;
    double cp = fluid->density * fluid->h / dt;

    for (int iter = 0; iter < numIters; iter++) {

#if RESOLUTION >= 300
#pragma omp parallel for collapse(2)
#endif
        for (int i = 0; i < fluid->numX-1; i++) {
            for (int j = 0; j < fluid->numY-1; j++) {

                if (fluid->s[i*n + j] == 0.) continue;
                double s = fluid->s[i*n + j];
                double sx0 = fluid->s[(i-1)*n + j];
                double sx1 = fluid->s[(i+1)*n + j];
                double sy0 = fluid->s[i*n + j-1];
                double sy1 = fluid->s[i*n + j+1];
                s = sx0 + sx1 + sy0 + sy1;

                if (s == 0.) continue;

                double div = fluid->u[ (i+1)*n + j] - fluid->u[i*n + j] +
                    fluid->v[i*n + j+1] - fluid->v[i*n + j];

                double p = -div / s;
                p *= OVER_RELAX;
                fluid->p[i*n + j] += cp * p;
                fluid->u[i*n + j] -= sx0 * p;
                fluid->u[(i+1)*n + j] += sx1 * p;
                fluid->v[i*n + j] -= sy0 * p;
                fluid->v[i*n + j+1] += sy1 * p;
            }
        }
    }
}

static void extrapolate(Fluid* fluid) {
    int n = fluid->numY;
    for (int i = 0; i < fluid->numX; i++) {
        fluid->u[i*n + 0] = fluid->u[i*n + 1];
        fluid->u[i*n + fluid->numY-1] = fluid->u[i*n + fluid->numY-2]; 
    }
    for (int j = 0; j < fluid->numY; j++) {
        fluid->v[0*n + j] = fluid->v[1*n + j];
        fluid->v[(fluid->numX-1)*n + j] = fluid->v[(fluid->numX-2)*n + j];
    }
}

double sampleField(Fluid* fluid, double x, double y, FieldType field) {
    int n = fluid->numY;
    double h = fluid->h;
    double h1 = 1. / h;
    double h2 = .5 * h;

    x = findMax( findMin(x, fluid->numX * h), h );
    y = findMax( findMin(y, fluid->numY * h), h );

    double dx = 0.;
    double dy = 0.;

    double* f;

    switch(field) {
        case U_FIELD: {
            f = fluid->u;
            dx = h2;
            break;
        }
        case V_FIELD: {
            f = fluid->v;
            dx = h2;
            break;
        }
        case S_FIELD: {
            f = fluid->m;
            dx = h2;
            dy = h2;
            break;
        }
    }

    double x0 = findMin( floor((x-dx)*h1), (double)fluid->numX-1.);
    double tx = ((x-dx) - x0*h) * h1;
    double x1 = findMin( x0+1., (double)fluid->numX-1. );

    double y0 = findMin( floor((y-dy)*h1), (double)fluid->numY-1.);
    double ty = ((y-dy) - y0*h) * h1;
    double y1 = findMin( y0+1., (double)fluid->numY-1. );

    double sx = 1. - tx;
    double sy = 1. - ty;

    double val = sx*sy * f[(int)(x0*n + y0)] +
				 tx*sy * f[(int)(x1*n + y0)] +
				 tx*ty * f[(int)(x1*n + y1)] +
				 sx*ty * f[(int)(x0*n + y1)];
    return val;
}

static double avgU(Fluid* fluid, int i, int j) {
    int n = fluid->numY;
    double u = (fluid->u[i*n + j-1] +
                fluid->u[i*n + j] +
                fluid->u[(i+1)*n + j-1] +
                fluid->u[(i+1)*n + j]) * 0.25;
    return u;
        
}

static double avgV(Fluid* fluid, int i, int j) {
    int n = fluid->numY;
    double v = (fluid->v[(i-1)*n + j] +
                fluid->v[i*n + j] +
                fluid->v[(i-1)*n + j+1] +
                fluid->v[i*n + j+1]) * 0.25;
    return v;
}

static void advectVel(Fluid* fluid, double dt) {
    memcpy(fluid->newU, fluid->u, sizeof(double)*fluid->numCells);
    memcpy(fluid->newV, fluid->v, sizeof(double)*fluid->numCells);
    
    int n = fluid->numY;
    double h = fluid->h;
    double h2 = .5 * h;

#if RESOLUTION >= 300
#pragma omp parallel for collapse(2)
#endif
    for (int i = 1; i < fluid->numX; i++) {
        for (int j = 1; j < fluid->numY; j++) {

            // u component
            if (fluid->s[i*n + j] != 0. &&
                fluid->s[(i-1)*n + j] != 0. && 
                j < fluid->numY - 1) {
                double x = ((double)i) * h;
                double y = ((double)j) * h + h2;

                double u = fluid->u[i*n + j];
                double v = avgV(fluid, i, j);

                x = x - dt*u;
                y = y - dt*v;
                u = sampleField(fluid, x, y, U_FIELD);
                fluid->newU[i*n + j] = u;
            }

            // v component
            if (fluid->s[i*n + j] != 0. &&
                fluid->s[i*n + j-1] != 0. &&
                i < fluid->numX - 1) {
                double x = ((double)i) * h + h2;
                double y = ((double)j) * h;
                double u = avgU(fluid, i, j);
                double v = fluid->v[i*n + j];
                x = x - dt*u;
                y = y - dt*v;
                v = sampleField(fluid, x, y, V_FIELD);
                fluid->newV[i*n + j] = v;
            }
        }
    }
    memcpy(fluid->u, fluid->newU, sizeof(double)*fluid->numCells);
    memcpy(fluid->v, fluid->newV, sizeof(double)*fluid->numCells);
}

static void advectSmoke(Fluid* fluid, double dt) {
    memcpy(fluid->newM, fluid->m, sizeof(double)*fluid->numCells);

    int n = fluid->numY;
    double h = fluid->h;
    double h2 = .5 * h;

#if RESOLUTION >= 300
#pragma omp parallel for collapse(2)
#endif
    for (int i = 1; i < fluid->numX-1; i++) {
        for (int j = 1; j < fluid->numY-1; j++) {
            if (fluid->s[i*n + j] != 0.) {
                double u = ( fluid->u[i*n + j] + fluid->u[(i+1)*n + j] )*.5;
                double v = ( fluid->v[i*n + j] + fluid->v[i*n + j] )*.5;
                double x = ((double)i)*h + h2 - dt*u;
                double y = ((double)j)*h + h2 - dt*v;
                fluid->newM[i*n + j] = sampleField(fluid, x,y, S_FIELD);
            }
        }
    }
    memcpy(fluid->m, fluid->newM, sizeof(double)*fluid->numCells);
}

void simulate(Fluid* fluid, Obstacle* obstacle, double dt, double gravity, int numIters) {
    integrate(fluid, dt, gravity, obstacle);

    // update obstacle for each dt
    updateObstacleTheta(obstacle);

    // initialize P each time.
    fluid->p = initArray(fluid->numCells, 0.);

    solveIncompress(fluid, numIters, dt);
    extrapolate(fluid);
    advectVel(fluid, dt);
    advectSmoke(fluid, dt);
}

