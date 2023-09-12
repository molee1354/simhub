#include <stdlib.h>

#include "fluid.h"
#include "utils.h"

#define ZEROS() initArray(fluid.numCells, 0.)
#define ONES() initArray(fluid.numCells, 1.)

/* Global Fluid instance */
Fluid fluid;

static int count = 0;

static double* initArray(int size, double elem);

void initFluid(double density, int numX, int numY, double h) {
    fluid.density = density;
    fluid.numX = numX + 2;
    fluid.numY = numY + 2;
    fluid.numCells = fluid.numX * fluid.numY;
    fluid.h = h;

    fluid.u = ZEROS();
    fluid.v = ZEROS();
    fluid.newU = ZEROS();
    fluid.newV = ZEROS();
    fluid.p = ZEROS();
    fluid.s = ZEROS();
    fluid.m = ONES();
    fluid.newM = ZEROS();

    fluid.num = numX * numY;
}

void freeFluid() {
    free(fluid.u);
    free(fluid.v);
    free(fluid.p);
    free(fluid.s);
    free(fluid.m);
    free(fluid.newU);
    free(fluid.newV);
    free(fluid.newM);
}

static double* initArray(int size, double elem) {
    double* out = (double*)malloc(sizeof(double) * size);
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
static void integrate(double dt, double gravity) {
    int n = fluid.numY;
    for (int i = 1; i < fluid.numX; i++) {
        for (int j = 1; j < fluid.numY-1; j++) {
            if (fluid.s[i*n + j] != 0. && fluid.s[i*n + j-1] != 0.) {
                fluid.v[i*n + j] += gravity*dt;
            }
        }
    }
}

static void solveIncompress(int numIters, double dt) {
    int n = fluid.numY;
    double cp = fluid.density * fluid.h / dt;

    for (int iter = 0; iter < numIters; iter++) {
        for (int i = 0; i < fluid.numX-1; i++) {
            for (int j = 0; j < fluid.numY-1; j++) {

                if (fluid.s[i*n + j] == 0.) continue;
                double s = fluid.s[i*n + j];
                double sx0 = fluid.s[(i-1)*n + j];
                double sx1 = fluid.s[(i+1)*n + j];
                double sy0 = fluid.s[i*n + j-1];
                double sy1 = fluid.s[i*n + j+1];
                s = sx0 + sx1 + sy0 + sy1;

                if (s == 0.) continue;

                double div = fluid.u[ (i+1)*n + j] - fluid.u[i*n + j] +
                    fluid.v[i*n + j+1] - fluid.v[i*n + j];

                double p = -div / s;
                p *= OVER_RELAX;
                fluid.p[i*n + j] += cp * p;
                fluid.u[i*n + j] -= sx0 * p;
                fluid.u[(i+1)*n + j] += sx1 * p;
                fluid.v[i*n + j] -= sy0 * p;
                fluid.v[i*n + j+1] += sy1 * p;
            }
        }
    }
}

static void extrapolate() {
    int n = fluid.numY;
    for (int i = 0; i < fluid.numX; i++) {
        fluid.u[i*n + 0] = fluid.u[i*n + 1];
        fluid.u[i*n + fluid.numY-1] = fluid.u[i*n + fluid.numY-2]; 
    }
    for (int j = 0; j < fluid.numY; j++) {
        fluid.v[0*n + j] = fluid.v[1*n + j];
        fluid.v[(fluid.numX-1)*n + j] = fluid.v[(fluid.numX-2)*n + j];
    }
}

static double sampleField(double x, double y, FieldType field) {
    int n = fluid.numY;
    double h = fluid.h;
    double h1 = 1. / h;
    double h2 = .5 * h;

    x = findMax( findMin(x, fluid.numX * h), h );
    y = findMax( findMin(y, fluid.numY * h), h );

    double dx = 0.;
    double dy = 0.;

    double* f;

    switch(field) {
        case U_FIELD: {
            f = fluid.u;
            dx = h2;
            break;
        }
        case V_FIELD: {
            f = fluid.v;
            dx = h2;
            break;
        }
        case S_FIELD: {
            f = fluid.m;
            dx = h2;
            dy = h2;
            break;
        }
    }

    double x0 = findMin( floor((x-dx)*h1), (double)fluid.numX-1.);
    double tx = ((x-dx) - x0*h) * h1;
    double x1 = findMin( x0+1., (double)fluid.numX-1. );

    double y0 = findMin( floor((y-dy)*h1), (double)fluid.numY-1.);
    double ty = ((y-dy) - y0*h) * h1;
    double y1 = findMin( y0+1., (double)fluid.numY-1. );

    double sx = 1. - tx;
    double sy = 1. - ty;

    double val = sx*sy * f[(int)(x0*n + y0)] +
				 tx*sy * f[(int)(x1*n + y0)] +
				 tx*ty * f[(int)(x1*n + y1)] +
				 sx*ty * f[(int)(x0*n + y1)];
    return val;
}

static double avgU(int i, int j) {
			int n = fluid.numY;
			double u = (fluid.u[i*n + j-1] + fluid.u[i*n + j] +
				fluid.u[(i+1)*n + j-1] + fluid.u[(i+1)*n + j]) * 0.25;
			return u;
				
		}

static double avgV(int i, int j) {
    int n = fluid.numY;
    double v = (fluid.v[(i-1)*n + j] + fluid.v[i*n + j] +
        fluid.v[(i-1)*n + j+1] + fluid.v[i*n + j+1]) * 0.25;
    return v;
}

static void advectVel(double dt) {
    memcpy(fluid.newU, fluid.u, fluid.numCells);
    memcpy(fluid.newV, fluid.v, fluid.numCells);
    
    int n = fluid.numY;
    double h = fluid.h;
    double h2 = .5 * h;

    for (int i = 1; i < fluid.numX; i++) {
        for (int j = 1; j < fluid.numY; j++) {
            count++;

            // u component
            if (fluid.s[i*n + j] != 0. &&
                fluid.s[(i-1)*n + j] != 0. && 
                j < fluid.numY - 1) {
                double x = ((double)i) * h;
                double y = ((double)j) * h + h2;

                double u = fluid.u[i*n + j];
                double v = avgV(i, j);

                x = x - dt*u;
                y = y - dt*v;
                u = sampleField(x, y, U_FIELD);
                fluid.newU[i*n + j] = u;
            }

            // v component
            if (fluid.s[i*n + j] != 0. &&
                fluid.s[i*n + j-1] != 0. &&
                i < fluid.numX - 1) {
                double x = ((double)i) * h + h2;
                double y = ((double)j) * h;
                double u = avgU(i, j);
                double v = fluid.v[i*n + j];
                x = x - dt*u;
                y = y - dt*v;
                v = sampleField(x, y, V_FIELD);
                fluid.newV[i*n + j] = v;
            }
        }
    }
    memcpy(fluid.u, fluid.newU, fluid.numCells);
    memcpy(fluid.v, fluid.newV, fluid.numCells);

}

static void advectSmoke(double dt) {
    memcpy(fluid.newM, fluid.m, fluid.numCells);

    int n = fluid.numY;
    double h = fluid.h;
    double h2 = .5 * h;

    for (int i = 1; i < fluid.numX-1; i++) {
        for (int j = 1; j < fluid.numY-1; j++) {
            if (fluid.s[i*n + j] != 0.) {
                double u = ( fluid.u[i*n + j] + fluid.u[(i+1)*n + j] )*.5;
                double v = ( fluid.v[i*n + j] + fluid.v[i*n + j] )*.5;
                double x = ((double)i)*h + h2 - dt*u;
                double y = ((double)j)*h + h2 - dt*v;
                fluid.newM[i*n + j] = sampleField(x,y, S_FIELD);
            }
        }
    }
    memcpy(fluid.m, fluid.newM, fluid.numCells);
}

void simulate(double dt, double gravity, int numIters) {
    integrate(dt, gravity);

    solveIncompress(numIters, dt);
    extrapolate();
    advectVel(dt);
    advectSmoke(dt);

    freeFluid();
}

