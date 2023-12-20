#include "particles_commonincl.h"
#include <math.h>

Table* makeTable(double spacing, int numObj) {
    Table* out = (Table*)malloc(sizeof(Table));
    out->spacing = spacing;
    out->tableSize = 2*numObj;
    out->cellStart = makeArray_int(out->tableSize+1);
    out->cellEntries = makeArray_int(numObj);
    out->queryIds = makeArray_int(numObj);
    out->querySize = 0;
    return out;
}

void freeTable(Table* table) {
    freeArray(table->cellStart);
    freeArray(table->cellEntries);
    freeArray(table->queryIds);
    free(table);
}

int hashCoords(Table* table, int x0, int y0, int z0) {
    int h = (x0 * 92837111) ^ (y0 * 689287499) ^ (z0 * 283923481);
    return abs(h) % table->tableSize;
}

int intCoord(Table* table, double coord) {
    return (int)floor(coord / table->spacing);
}

int hashPos(Table* table, array_double* pos, int nr) {
    return hashCoords(table,
                      intCoord(table, pos->values[3*nr]),
                      intCoord(table, pos->values[3*nr + 1]),
                      intCoord(table, pos->values[3*nr + 2])
                      );
}

void create(Table* table, array_double* pos) {
    int numObj = (int)findMin(pos->count/3, table->cellEntries->capacity);
    for (int i = 0; i < numObj; i++) {
        int h = hashPos(table, pos, i);
        table->cellStart->values[h]++;
    }
    int start = 0;
    for (int i = 0; i < table->tableSize; i++) {
        start += table->cellStart->values[i];
        table->cellStart->values[i] = start;
    }
    table->cellStart->values[table->tableSize] = start;

    for (int i = 0; i < numObj; i++) {
        int h = hashPos(table, pos, i);
        table->cellStart->values[h]--;
        table->cellEntries->values[table->cellStart->values[h]] = i;
    }
}

void query(Table* table, array_double* pos, int nr, double maxDist) {
    int x0 = intCoord(table, pos->values[3*nr]     - maxDist);
    int y0 = intCoord(table, pos->values[3*nr + 1] - maxDist);
    int z0 = intCoord(table, pos->values[3*nr + 2] - maxDist);

    int x1 = intCoord(table, pos->values[3*nr]     + maxDist);
    int y1 = intCoord(table, pos->values[3*nr + 1] + maxDist);
    int z1 = intCoord(table, pos->values[3*nr + 2] + maxDist);

    table->querySize = 0;

    for (int xi = x0; xi <= x1; xi++) {
        for (int yi = y0; yi <= y1; yi++) {
            for (int zi = z0; zi <= z1; zi++) {
                int h = hashCoords(table, xi, yi, zi);
                int start = table->cellStart->values[h];
                int end = table->cellStart->values[h+1];

                for (int i = start; i < end; i++) {
                    table->queryIds->values[table->querySize] = table->cellEntries->values[i];
                    table->querySize++;
                }
            }
        }
    }
}
