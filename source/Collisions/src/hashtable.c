#include "collisions_commonincl.h"
#include <math.h>


Table* makeTable(double spacing, int numObj) {
    Table* out = (Table*)malloc(sizeof(Table));
    out->spacing = spacing;
    out->tableSize = 2*numObj;
    out->cellStart = ALLOCATE(int, out->tableSize+1);
    out->cellEntries = ALLOCATE(int, numObj);
    out->queryIds = ALLOCATE(int, numObj);
    out->querySize = 0;
    return out;
}

int hashCoords(Table* table, int x0, int y0, int z0) {
    int h = (x0 * 92837111) ^ (y0 * 689287499) ^ (z0 * 283923481);
    return abs(h) % table->tableSize;
}

int intCoord(Table* table, double coord) {
    return (int)floor(coord / table->spacing);
}

int hashPos(Table* table, int* positions, int nr) {
    return hashCoords(table,
                      intCoord(table, positions[3*nr]),
                      intCoord(table, positions[3*nr + 1]),
                      intCoord(table, positions[3*nr + 2])
                      );
}

void create(Table* table, int* positions) {
    int length = sizeof(positions) / sizeof(positions[0]);
}

void query(Table* table, int* pos, int nr, double maxDist);
