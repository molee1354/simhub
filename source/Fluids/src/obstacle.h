#ifndef simhub_obstacle_h
#define simhub_obstacle_h

typedef struct {
    int x;
    int y;

    double radius; // set double because units in terms of radio

    double theta; // orientation of the obstacle
    double omega; // angular velocity of the obstacle
} Obstacle;

/**
 * @brief Function to initialize the obstacle
 *
 * @param setX x-coordinate
 * @param setY y-coordinate
 * @param radius radius
 * @return Obstacle* pointer to an obstacle object
 */
Obstacle* initObstacle(int setX, int setY, double radius);

/**
 * @brief Function to free the obstacle object
 *
 * @param obstacle Pointer to obstacle to free
 */
void freeObstacle(Obstacle* obstacle);

#endif
