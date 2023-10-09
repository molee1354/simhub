#include "fluids_commonincl.h"

Obstacle* initObstacle(int setX, int setY, double radius) {
    Obstacle* out = (Obstacle*)malloc(sizeof(Obstacle));
    out->x = setX;
    out->y = setY;
    out->radius = radius;

    out->theta = 0.;
    out->omega = 0.;

    return out;
}

void freeObstacle(Obstacle* obstacle) {
    free(obstacle);
}
