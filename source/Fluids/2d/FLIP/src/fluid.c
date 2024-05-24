#include "fluids_commonincl.h"
#include <limits.h>
#include <math.h>

double xDistConv(double index, double scaleH, double setX) {
    return (index + .5) * scaleH - (DOMAIN_WIDTH / WINDOW_WIDTH) * setX;
}

double yDistConv(double index, double scaleH, double setY) {
    return (index + .5) * scaleH - (DOMAIN_HEIGHT / WINDOW_HEIGHT) * setY;
}

Fluid* initFluid(double density, double spacing, double particleRad, int width,
                 int height, int maxParticles) {
    Fluid* out = (Fluid*)malloc(sizeof(Fluid));

    out->density = density;
    out->fNumX = (int)floor((double)width / spacing) + 1;
    out->fNumY = (int)floor((double)height / spacing) + 1;
    out->h = findMax((double)width / (double)out->fNumX,
                     (double)height / (double)out->fNumY);
    out->fInvSpacing = 1. / out->h;
    out->fNumCells = out->fNumX * out->fNumY;

    int fNumCells = out->fNumCells;
    out->u = new_vector(fNumCells);
    out->v = new_vector(fNumCells);
    out->du = new_vector(fNumCells);
    out->dv = new_vector(fNumCells);
    out->prevU = new_vector(fNumCells);
    out->prevV = new_vector(fNumCells);
    out->p = new_vector(fNumCells);
    out->s = new_vector(fNumCells);
    out->cellType = new_vector(fNumCells);      // int
    out->cellColor = new_vector(3 * fNumCells); // float

    // Particles
    out->maxParticles = maxParticles;
    out->particlePos = new_vector(2 * maxParticles);
    out->particleColor = new_vector(3 * maxParticles);
    printf("len : %d\n", LENGTH(out->particleColor));
    for (int i = 0; i < maxParticles; i++)
        out->particleColor[3 * i + 3] = 1.;

    out->particleVel = new_vector(2 * maxParticles);
    out->particleDensity = new_vector(fNumCells);
    out->particleRestDensity = 0.;
    out->particleRadius = particleRad;
    out->pInvSpacing = 1. / (2.2 * particleRad);
    out->pNumX = (int)floor((double)width / out->pInvSpacing) + 1;
    out->pNumY = (int)floor((double)height / out->pInvSpacing) + 1;
    out->pNumCells = out->pNumX * out->pNumY;

    int pNumCells = out->pNumCells;
    out->numCellParticles = new_vector(pNumCells);      // int
    out->firstCellParticle = new_vector(pNumCells + 1); // int
    out->cellParticleIds = new_vector(maxParticles);    // int

    out->numParticles = 0;

    return out;
}

/**
 * @brief Function to integrate the particle's position and velocity
 *
 * @param fluid Pointer to fluid
 * @param dt Delta t
 * @param gravity Gravity
 */
static void integrateParticles(Fluid* fluid, double dt, double gravity) {
    for (int i = 0; i < fluid->numParticles; i++) {
        fluid->particleVel[2 * i + 1] += dt * gravity;
        fluid->particlePos[2 * i] += fluid->particleVel[2 * i] * dt;
        fluid->particlePos[2 * i + 1] += fluid->particleVel[2 * i + 1] * dt;
    }
}

static void pushParticles(Fluid* fluid, int numIters) {
    double colorDiffusionCoeff = .001;

    for (int i = 0; i < LENGTH(fluid->numCellParticles); i++)
        fluid->numCellParticles[i] = 0.;

    for (int i = 0; i < fluid->numParticles; i++) {
        double x = fluid->particlePos[2 * i];
        double y = fluid->particlePos[2 * i + 1];

        double xi = clamp(floor(x * fluid->pInvSpacing), 0., fluid->pNumX - 1.);
        double yi = clamp(floor(y * fluid->pInvSpacing), 0., fluid->pNumY - 1.);
        int cellNr = (int)xi * fluid->pNumY + (int)yi;
        fluid->numCellParticles[cellNr]++;
    }
    // partial sums
    int first = 0;
    for (int i = 0; i < fluid->pNumCells; i++) {
        first += fluid->numCellParticles[i];
        fluid->firstCellParticle[i] = first;
    }
    fluid->firstCellParticle[fluid->pNumCells] = first;

    // fill particles into cells
    for (int i = 0; i < fluid->numParticles; i++) {
        double x = fluid->particlePos[2 * i];
        double y = fluid->particlePos[2 * i + 1];

        double xi = clamp(floor(x * fluid->pInvSpacing), 0, fluid->pNumX - 1);
        double yi = clamp(floor(y * fluid->pInvSpacing), 0, fluid->pNumY - 1);
        int cellNr = (int)xi * fluid->pNumY + (int)yi;
        fluid->firstCellParticle[cellNr]--;
        fluid->cellParticleIds[(int)fluid->firstCellParticle[cellNr]] = i;
    }

    // push particles apart
    double minDist = 2.0 * fluid->particleRadius;
    double minDist2 = minDist * minDist;

    for (int iter = 0; iter < numIters; iter++) {
        for (int i = 0; i < fluid->numParticles; i++) {
            double px = fluid->particlePos[2 * i];
            double py = fluid->particlePos[2 * i + 1];

            int pxi = (int)floor(px * fluid->pInvSpacing);
            int pyi = (int)floor(py * fluid->pInvSpacing);

            int x0 = (int)findMax(pxi - 1, 0);
            int y0 = (int)findMax(pyi - 1, 0);

            int x1 = (int)findMin(pxi + 1, fluid->pNumX - 1);
            int y1 = (int)findMin(pyi + 1, fluid->pNumY - 1);

            for (int xi = x0; xi <= x1; xi++) {
                for (int yi = y0; yi <= y1; yi++) {
                    int cellNr = xi * fluid->pNumY + yi;
                    int first = fluid->firstCellParticle[cellNr];
                    int last = fluid->firstCellParticle[cellNr + 1];
                    for (int j = first; j < last; j++) {

                        int id = fluid->cellParticleIds[j];

                        if (id == 1)
                            continue;
                        // TODO : check idx here
                        double qx = fluid->particlePos[2 * id];
                        double qy = fluid->particlePos[2 * id + 1];

                        double dx = qx - px;
                        double dy = qy - py;
                        double d2 = dx * dx + dy * dy;

                        if (d2 > minDist2 || d2 == 0.)
                            continue;

                        double d = sqrt(d2);
                        double s = .5 * (minDist - d) / d;
                        dx *= s;
                        dy *= s;
                        fluid->particlePos[2 * i] -= dx;
                        fluid->particlePos[2 * i + 1] -= dy;
                        fluid->particlePos[2 * id] += dx;
                        fluid->particlePos[2 * id + 1] += dy;

                        // diffusing colors
                        for (int rgb = 0; rgb < 3; rgb++) {
                            float color0 = fluid->particleColor[3 * i + rgb];
                            float color1 = fluid->particleColor[3 * id + rgb];
                            float color = .5 * (color0 + color1);
                            fluid->particleColor[3 * i + rgb] =
                                color0 + (color - color0) + colorDiffusionCoeff;
                            fluid->particleColor[3 * id + rgb] =
                                color1 + (color - color1) + colorDiffusionCoeff;
                        }
                    }
                }
            }
        }
    }
}

static void handleParticleCollisions(Fluid* fluid, Obstacle* obstacle,
                                     double obsX, double obsY, double obsR) {
    double h = 1. / fluid->fInvSpacing;
    double r = fluid->particleRadius;
    double obsR2 = obsR * obsR;
    double minDist = obsR + r;
    double minDist2 = minDist * minDist;

    double minX = h + r;
    double maxX = (fluid->fNumX - 1) * h - r;
    double minY = h + r;
    double maxY = (fluid->fNumY - 1) * h - r;

    // iterating over particles
    for (int i = 0; i < fluid->numParticles; i++) {
        double x = fluid->particlePos[2 * i];
        double y = fluid->particlePos[2 * i + 1];

        double dx = x - obsX;
        double dy = y - obsY;
        double d2 = dx * dx + dy * dy;

        // obstacle collision
        if (d2 < minDist2) {
            fluid->particleVel[2 * i] = obstacle->vx;
            fluid->particleVel[2 * i + 1] = obstacle->vy;
        }

        // wall collision
        if (x < minX) {
            x = minX;
            fluid->particleVel[2 * i] = 0.;
        }
        if (x > maxX) {
            x = maxX;
            fluid->particleVel[2 * i] = 0.;
        }
        if (y < minY) {
            y = minY;
            fluid->particleVel[2 * i + 1] = 0.;
        }
        if (y > maxY) {
            y = maxY;
            fluid->particleVel[2 * i + 1] = 0.;
        }
        fluid->particlePos[2 * i] = x;
        fluid->particlePos[2 * i + 1] = y;
    }
}

static void updateParticleDensity(Fluid* fluid) {
    int n = fluid->fNumY;
    double h = fluid->h;
    double h1 = fluid->fInvSpacing;
    double h2 = fluid->h * .5;
    double* d = fluid->particleDensity;

    for (int i = 0; i < fluid->numParticles; i++) {
        double x = fluid->particlePos[2 * i];
        double y = fluid->particlePos[2 * i + 1];

        x = clamp(x, h, (fluid->fNumX - 1) * h);
        y = clamp(y, h, (fluid->fNumY - 1) * h);

        double x0 = floor((x - h2) * h1);
        double tx = ((x - h2) - x0 * h) * h1;
        double x1 = findMin(x0 + 1, fluid->fNumX - 2);

        double y0 = floor((y - h2) * h1);
        double ty = ((y - h2) - y0 * h) * h1;
        double y1 = findMin(y0 + 1, fluid->fNumY - 2);

        double sx = 1. - tx;
        double sy = 1. - ty;

        // TODO : maybe add +1 to d idx?
        if (x0 < fluid->fNumX && y0 < fluid->fNumY)
            d[(int)x0 * n + (int)y0] += sx * sy;
        if (x1 < fluid->fNumX && y0 < fluid->fNumY)
            d[(int)x1 * n + (int)y0] += tx * sy;
        if (x1 < fluid->fNumX && y1 < fluid->fNumY)
            d[(int)x1 * n + (int)y1] += tx * ty;
        if (x0 < fluid->fNumX && y1 < fluid->fNumY)
            d[(int)x0 * n + (int)y1] += sx * ty;
    }
    if (fluid->particleRestDensity == 0.) {
        double sum = 0.;
        int numFluidCells = 0;

        for (int i = 0; i < fluid->fNumCells; i++) {
            if (fluid->cellType[i] == FLUID_CELL) {
                sum += d[i];
                numFluidCells++;
            }
        }
        if (numFluidCells > 0) {
            fluid->particleRestDensity = sum / numFluidCells;
        }
    }
}

static void transferVelocity(Fluid* fluid, bool toGrid, double flipRatio) {
    int n = fluid->fNumY;
    double h = fluid->h;
    double h1 = fluid->fInvSpacing;
    double h2 = fluid->h * .5;

    if (toGrid) {
        memcpy(fluid->prevU, fluid->u, sizeof(double) * fluid->fNumCells);
        memcpy(fluid->prevV, fluid->v, sizeof(double) * fluid->fNumCells);

        for (int i = 0; i < fluid->fNumCells; i++)
            fluid->cellType[i] = fluid->s[i] == 0. ? SOLID_CELL : AIR_CELL;

        for (int i = 0; i < fluid->numParticles; i++) {
            double x = fluid->particlePos[2 * i];
            double y = fluid->particlePos[2 * i + 1];
            double xi = clamp(floor(x * h1), 0, fluid->fNumX - 1);
            double yi = clamp(floor(y * h1), 0, fluid->fNumY - 1);
            int cellNr = (int)xi * n + (int)yi;
            if (fluid->cellType[cellNr] == AIR_CELL)
                fluid->cellType[cellNr] = FLUID_CELL;
        }
    }

    // looping over both u and v components
    for (int component = 0; component < 2; component++) {
        double dx = component == 0 ? 0. : h2;
        double dy = component == 0 ? h2 : 0.;

        vector f = component == 0 ? fluid->u : fluid->v;
        vector prevF = component == 0 ? fluid->prevU : fluid->prevV;
        vector d = component == 0 ? fluid->du : fluid->dv;

        for (int i = 0; i < fluid->numParticles; i++) {
            double x = fluid->particlePos[2 * i];
            double y = fluid->particlePos[2 * i + 1];

            x = clamp(x, h, (fluid->fNumX - 1) * h);
            y = clamp(y, h, (fluid->fNumY - 1) * h);

            double x0 = findMin(floor((x - dx) * h1), fluid->fNumX - 2);
            double tx = ((x - dx) - x0 * h) * h1;
            double x1 = findMin(x0 + 1, fluid->fNumX - 2);

            double y0 = findMin(floor((y - dy) * h1), fluid->fNumY - 2);
            double ty = ((y - dy) - y0 * h) * h1;
            double y1 = findMin(y0 + 1, fluid->fNumY - 2);

            double sx = 1. - tx;
            double sy = 1. - ty;

            double d0 = sx * sy;
            double d1 = tx * sy;
            double d2 = tx * ty;
            double d3 = sx * ty;

            int nr0 = (int)x0 * n + (int)y0;
            int nr1 = (int)x1 * n + (int)y0;
            int nr2 = (int)x1 * n + (int)y1;
            int nr3 = (int)x0 * n + (int)y1;

            if (toGrid) {
                double pv = fluid->particleVel[2 * i + component];
                f[nr0] += pv * d0;
                d[nr0] += d0;
                f[nr1] += pv * d1;
                d[nr1] += d1;
                f[nr2] += pv * d2;
                d[nr2] += d2;
                f[nr3] += pv * d3;
                d[nr3] += d3;
            } else {
                int offset = component == 0 ? n : 1;

                double valid0 =
                    fluid->cellType[nr0] != AIR_CELL ||
                            fluid->cellType[nr0 - offset] != AIR_CELL
                        ? 1.0
                        : 0.0;
                double valid1 =
                    fluid->cellType[nr1] != AIR_CELL ||
                            fluid->cellType[nr1 - offset] != AIR_CELL
                        ? 1.0
                        : 0.0;
                double valid2 =
                    fluid->cellType[nr2] != AIR_CELL ||
                            fluid->cellType[nr2 - offset] != AIR_CELL
                        ? 1.0
                        : 0.0;
                double valid3 =
                    fluid->cellType[nr3] != AIR_CELL ||
                            fluid->cellType[nr3 - offset] != AIR_CELL
                        ? 1.0
                        : 0.0;

                double v = fluid->particleVel[2 * i + component];
                double d =
                    valid0 * d0 + valid1 * d1 + valid2 * d2 + valid3 * d3;

                if (d > 0.) {
                    double picV =
                        (valid0 * d0 * f[nr0] + valid1 * d1 * f[nr1] +
                         valid2 * d2 * f[nr2] + valid3 * d3 * f[nr3]) /
                        d;
                    double corr = (valid0 * d0 * (f[nr0] - prevF[nr0]) +
                                   valid1 * d1 * (f[nr1] - prevF[nr1]) +
                                   valid2 * d2 * (f[nr2] - prevF[nr2]) +
                                   valid3 * d3 * (f[nr3] - prevF[nr3])) /
                                  d;
                    double flipV = v + corr;

                    fluid->particleVel[2 * i + component] =
                        (1.0 - flipRatio) * picV + flipRatio * flipV;
                }
            }
        }
        if (toGrid) {
            for (int i = 0; i < fluid->fNumCells; i++) {
                if (d[i] > 0.0)
                    f[i] /= d[i];
            }

            // restoring solid cells
            for (int i = 0; i < fluid->fNumX; i++) {
                for (int j = 0; j < fluid->fNumY; j++) {
                    bool solid = fluid->cellType[i * n + j] == SOLID_CELL;
                    if (solid || (i > 0 && fluid->cellType[(i - 1) * n + j] ==
                                               SOLID_CELL))
                        fluid->u[i * n + j] = fluid->prevU[i * n + j];
                    if (solid ||
                        (j > 0 && fluid->cellType[i * n + j - 1] == SOLID_CELL))
                        fluid->v[i * n + j] = fluid->prevV[i * n + j];
                }
            }
        }
    }
}

static void solveIncompressibility(Fluid* fluid, int numIters, double dt,
                                   bool drift) {
    memcpy(fluid->prevU, fluid->u, sizeof(double) * fluid->fNumCells);
    memcpy(fluid->prevV, fluid->v, sizeof(double) * fluid->fNumCells);

    int n = fluid->fNumY;
    double cp = fluid->density * fluid->h / dt;

    // REMOVE?
    for (int i = 0; i < fluid->fNumCells; i++) {
        double u = fluid->u[i];
        double v = fluid->v[i];
    }

    for (int iter = 0; iter < NUM_ITER; iter++) {
        for (int i = 1; i < fluid->fNumX - 1; i++) {
            for (int j = 1; j < fluid->fNumY - 1; j++) {
                if (fluid->cellType[i * n + j] != FLUID_CELL)
                    continue;

                int center = i * n + j;
                int left = (i - 1) * n + j;
                int right = (i + 1) * n + j;
                int bottom = i * n + j - 1;
                int top = i * n + j + 1;

                double s = fluid->s[center];
                double sx0 = fluid->s[left];
                double sx1 = fluid->s[right];
                double sy0 = fluid->s[bottom];
                double sy1 = fluid->s[top];
                s = sx0 + sx1 + sy0 + sy1;
                if (s == 0.)
                    continue;

                double div = fluid->u[right] - fluid->u[center] +
                             fluid->v[top] - fluid->v[center];
                if (fluid->particleRestDensity > 0. && drift == 1) {
                    double k = 1.;
                    double compression = fluid->particleDensity[i * n + j] -
                                         fluid->particleRestDensity;
                    if (compression > 0.)
                        div = div - k * compression;
                }

                double p = -div / s;
                p *= OVER_RELAX;
                fluid->p[center] += cp * p;
                fluid->u[center] -= sx0 * p;
                fluid->u[right] += sx1 * p;
                fluid->v[center] -= sy0 * p;
                fluid->v[top] += sy1 * p;
            }
        }
    }
}

static void updateParticleColors(Fluid* fluid) {
    double h1 = fluid->fInvSpacing;
    for (int i = 0; i < fluid->numParticles; i++) {
        double s = .01;
        fluid->particleColor[3 * i] =
            (float)clamp(fluid->particleColor[3 * i] - s, 0., 1.);
        fluid->particleColor[3 * i + 1] =
            (float)clamp(fluid->particleColor[3 * i + 1] - s, 0., 1.);
        fluid->particleColor[3 * i + 2] =
            (float)clamp(fluid->particleColor[3 * i + 2] - s, 0., 1.);
        double x = fluid->particlePos[2 * i];
        double y = fluid->particlePos[2 * i + 1];
        double xi = clamp(floor(x * h1), 1, fluid->fNumX - 1);
        double yi = clamp(floor(y * h1), 1, fluid->fNumY - 1);
        int cellNr = (int)xi + fluid->fNumY + (int)yi;

        double d0 = fluid->particleRestDensity;

        if (d0 > 0.) {
            double relativeRho = fluid->particleDensity[cellNr] / d0;
            if (relativeRho < 0.7) {
                double s = 0.8;
                fluid->particleColor[3 * i] = (float)s;
                fluid->particleColor[3 * i + 1] = (float)s;
                fluid->particleColor[3 * i + 2] = (float)1.;
            }
        }
    }
}

static void setSciColor(Fluid* fluid, int cellNr, double value, double minVal,
                        double maxVal) {
    value = findMin(findMax(value, minVal), maxVal - .0001);
    double d = maxVal - minVal;
    value = d == 0. ? .5 : (value - minVal) / d;

    double m = .25;
    int num = (int)floor(value / m);
    float s = (value - num * m) / m;
    float red, green, blue;
    switch (num) {
    case 0: {
        red = 0.0f;
        green = s;
        blue = 1.0f;
        break;
    }
    case 1: {
        red = 0.0f;
        green = 1.0f;
        blue = 1.0f - s;
        break;
    }
    case 2: {
        red = s;
        green = 1.0f;
        blue = 0.0f;
        break;
    }
    case 3: {
        red = 1.0f;
        green = 1.0f - s;
        blue = 0.0f;
        break;
    }
    }
    fluid->cellColor[3 * cellNr] = red;
    fluid->cellColor[3 * cellNr] = green;
    fluid->cellColor[3 * cellNr + 2] = blue;
}

static void updateCellColors(Fluid* fluid) {
    for (int i = 0; i < fluid->fNumCells; i++) {
        if (fluid->cellType[i] == SOLID_CELL) {
            fluid->cellColor[3 * i] = 0.5f;
            fluid->cellColor[3 * i + 1] = 0.5f;
            fluid->cellColor[3 * i + 2] = 0.5f;
        } else if (fluid->cellType[i] == FLUID_CELL) {
            double rho = fluid->particleDensity[i];
            if (fluid->particleRestDensity > 0.)
                rho /= fluid->particleRestDensity;
            setSciColor(fluid, i, rho, 0.0, 2.0);
        }
    }
}

void initialState(Fluid* fluid) {
    fluid->numParticles = fluid->maxParticles;
    int n = fluid->fNumY;
    for (int i = 0; i < fluid->fNumX; i++) {
        for (int j = 0; j < fluid->fNumY; j++) {
            double s = 1.; // fluid
            if (i == 0 || i == fluid->fNumX - 1 || j == 0)
                s = 0.; // solid
            fluid->s[i * n + j] = s;
        }
    }
}

void simulate(Fluid* fluid, Obstacle* obstacle, double dt, double gravity,
              int numIters) {
    double substeps = 1;
    double dt_sub = dt / substeps;

    for (int step = 0; step < substeps; step++) {
        fluid->p = new_vector(fluid->fNumCells);

        integrateParticles(fluid, dt_sub, gravity);
        if (PARTICLES_SEP == 1)
            pushParticles(fluid, numIters);
        handleParticleCollisions(fluid, obstacle, obstacle->x, obstacle->y,
                                 obstacle->radius);
        transferVelocity(fluid, true, 0.);
        updateParticleDensity(fluid);
        solveIncompressibility(fluid, numIters, dt_sub, DRIFT);
        transferVelocity(fluid, false, FLIP_RATIO);
    }
    updateParticleColors(fluid);
    updateCellColors(fluid);
}

void freeFluid(Fluid* fluid) {
    free_vector(fluid->u);
    free_vector(fluid->v);
    free_vector(fluid->du);
    free_vector(fluid->dv);
    free_vector(fluid->prevU);
    free_vector(fluid->prevV);
    free_vector(fluid->s);
    free_vector(fluid->cellType);
    free_vector(fluid->cellColor);

    free_vector(fluid->particlePos);
    free_vector(fluid->particleColor);
    free_vector(fluid->particleVel);
    free_vector(fluid->particleDensity);

    free_vector(fluid->numCellParticles);
    free_vector(fluid->firstCellParticle);
}
