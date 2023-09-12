#include <math.h>
#include <stdlib.h>
#include "fluid.h"
#include "utils.h"


/* Global Fluid instance */
Fluid fluid;

void initFluid(double density, int numX, int numY, double h) {
    fluid.density = density;
    fluid.numX = numX + 2;
    fluid.numY = numY + 2;
    fluid.numCells = fluid.numX * fluid.numY;
    fluid.h = h;

    Vector* uVec = zeros(fluid.numCells, ROW);
    fluid.u = makeModifiable(uVec);
    Vector* vVec = zeros(fluid.numCells, ROW);
    fluid.v = makeModifiable(vVec);
    Vector* newUVec = zeros(fluid.numCells, ROW);
    fluid.newU = makeModifiable(newUVec);
    Vector* newVVec = zeros(fluid.numCells, ROW);
    fluid.newV = makeModifiable(newVVec);
    Vector* pVec = zeros(fluid.numCells, ROW);
    fluid.p = makeModifiable(pVec);
    Vector* sVec = zeros(fluid.numCells, ROW);
    fluid.s = makeModifiable(sVec);
    Vector* mVec = ones(fluid.numCells, ROW);
    fluid.m = makeModifiable(mVec);
    Vector* newMVec = zeros(fluid.numCells, ROW);
    fluid.newM = makeModifiable(newMVec);

    fluid.num = numX * numY;
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

    double x0 = findMin( floor((x-dx)*h1), (double)fluid.numX-1);
    double tx = ((x-dx) - x0*h) * h1;
    double x1 = findMin( x0+1, (double)fluid.numX-1 );

    double y0 = findMin( floor((y-dy)*h1), (double)fluid.numY-1);
    double ty = ((y-dy) - y0*h) * h1;
    double y1 = findMin( y0+1, (double)fluid.numY-1 );

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

}
