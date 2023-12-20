#include "particles_commonincl.h"
#include <math.h>

Particles* initParticles(double radius, array_double* pos, array_double* vel) {
    Particles* out = (Particles*)malloc(sizeof(Particles));
    out->pos = pos;
    out->prevPos = pos;
    out->vel = vel;
    out->radius = radius;
    out->numParticles = pos->count / 3;
    out->table = makeTable(2. * radius, out->numParticles);
    out->showCollisions = true;
    out->normal = makeArray_double(3);
    out->colors = makeArray_float(3* out->numParticles);
    return out;
}

void freeParticles(Particles *particles) {
    freeArray(particles->pos);
    freeArray(particles->vel);
    freeArray(particles->prevPos);
    freeTable(particles->table);
    freeArray(particles->normal);
    freeArray(particles->colors);
}

void updateMesh(Particles* particles) {

}

void simulate(Particles* particles, double dt,
              array_double* gravity, array_int* bounds) {
    double minDist = 2. * particles->radius;
    for (int i = 0; i < particles->numParticles; i++) {
        vectorAdd(particles->vel, i, gravity, 0, dt);
        vectorCopy(particles->prevPos, i, particles->pos, i);
        vectorAdd(particles->pos, i, particles->vel, i, dt);
    }
    create(particles->table, particles->pos);

    // collisions
    for (int i = 0; i < particles->numParticles; i++) {
        /* code to set color here */

        // wall collisions
        for (int dim = 0; dim < 3; dim++) {
            int nr = 3*i + dim;
            if (particles->pos->values[nr] < bounds->values[dim] + particles->radius) {
                particles->pos->values[nr] = bounds->values[dim] + particles->radius;
                particles->vel->values[nr] = -particles->vel->values[nr];
                /* set collision color here */
            } else
            if (particles->pos->values[nr] > bounds->values[dim+3]+particles->radius) {
                particles->pos->values[nr] = bounds->values[dim+3] - particles->radius;
                particles->vel->values[nr] = -particles->vel->values[nr];
                /* set collision color here */
            }
        }
        query(particles->table, particles->pos, i, 2.*particles->radius);
        for (int nr = 0; nr < particles->table->querySize; nr++) {
            int j = particles->table->queryIds->values[nr];
            vectorSetDiff(particles->normal,0, particles->pos, i, particles->pos, j, 1.0);
            double d2 = vectorLenSquare(particles->normal, 0);

            // check for overlap
            if (d2 > 0. && d2 < minDist*minDist) {
                double d = sqrt(d2);
                vectorScale(particles->normal, 0, 1./d);
                double corr = (minDist - d) * .5;
                vectorAdd(particles->pos, i, particles->normal, 0, corr);
                vectorAdd(particles->pos, j, particles->normal, 0, -corr);

                double vi = vectorDot(particles->vel, i, particles->normal, 0);
                double vj = vectorDot(particles->vel, j, particles->normal, 0);
                vectorAdd(particles->vel, i, particles->normal, 0, vj-vi);
                vectorAdd(particles->vel, j, particles->normal, 0, vi-vj);
            }
        }
    }
}
