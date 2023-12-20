#ifndef simhub_collisions_hashtable_h
#define simhub_collisions_hashtable_h

#include <stdlib.h>
#include "sim.input"

typedef struct {
    double spacing;
    int tableSize;
    int* cellStart;
    int* cellEntries;
    int* queryIds;
    int querySize;
} Table;

/**
 * @brief Function to create a hash table
 *
 * @return Hashtable* Pointer to a hash table
 */
Table* makeTable(double spacing, int numObj);

/**
 * @brief Function to compute the hashed coordinates of a particle
 *
 * @param x0 
 * @param y0 
 * @param z0 
 * @return int The hashed coordinate of the particle
 */
int hashCoords(Table* table, int x0, int y0, int z0);

/**
 * @brief Function to return the integer coordinate value.
 *
 * @param coord Coordinate value
 * @return int An integer coordinate value
 */
int intCoord(Table* table, double coord);

/**
 * @brief Function to return the hashed coordinate of a particle
 *
 * @param positions Integer array of all positions
 * @param nr Integer index of particle
 * @return Int hashed coordinate of a particle
 */
int hashPos(Table* table, int* positions, int nr);

void create(Table* table, int* positions);

void query(Table* table, int* pos, int nr, double maxDist);

#endif
