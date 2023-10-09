#include "fluids_commonincl.h"

Obstacle* initObstacle(int setX, int setY, double radius) {
    Obstacle* out = (Obstacle*)malloc(sizeof(Obstacle));
    out->posX = setX;
    out->posY = setY;
    out->radius = radius;

    out->theta = 0.;
    out->omega = 0.;

    return out;
}

void freeObstacle(Obstacle* obstacle) {
    free(obstacle);
}
