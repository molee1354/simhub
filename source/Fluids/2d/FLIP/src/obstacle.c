#include "fluids_commonincl.h"

Obstacle* initObstacle(int setX, int setY, double radius) {
    Obstacle* out = (Obstacle*)malloc(sizeof(Obstacle));
    if (out==NULL) {
        printf("Error: could not allocate memory for obstacle struct.");
        return NULL;
    }
    out->x = setX;
    out->y = setY;
    out->dx = 0.;
    out->dy = 0.;
    out->vx = 0.;
    out->vy = 0.;
    out->radius = radius;

    out->theta = 0.;
    out->omega = 0.;

    return out;
}

void moveObstacle(Obstacle* obstacle, int newX, int newY) {
    obstacle->dx = newX - obstacle->x;
    obstacle->dy = newY - obstacle->y;
    obstacle->vx = obstacle->dx / (double)DT;
    obstacle->vy = obstacle->dy / (double)DT;
    obstacle->x = newX;
    obstacle->y = newY;
}

void freeObstacle(Obstacle* obstacle) {
    free(obstacle);
}
