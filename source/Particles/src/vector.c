#include "particles_commonincl.h"


void vectorScale_i(array_int* a, int anr, double scale) {
    anr *= 3;
    a->values[anr++] *= (int)scale;
    a->values[anr++] *= (int)scale;
    a->values[anr]   *= (int)scale;
}
void vectorScale_d(array_double* a, int anr, double scale) {
    anr *= 3;
    a->values[anr++] *= scale;
    a->values[anr++] *= scale;
    a->values[anr] *= scale;
}

void vectorScale_f(array_float* a, int anr, double scale) {
    anr *= 3;
    a->values[anr++] *= (float)scale;
    a->values[anr++] *= (float)scale;
    a->values[anr]   *= (float)scale;
}

void vectorCopy_i(array_int* a, int anr, array_int*b, int bnr) {
    anr *= 3;
    bnr *= 3;
    a->values[anr++] = b->values[bnr++];
    a->values[anr++] = b->values[bnr++];
    a->values[anr] = b->values[bnr];
}
void vectorCopy_d(array_double* a, int anr, array_double*b, int bnr) {
    anr *= 3;
    bnr *= 3;
    a->values[anr++] = b->values[bnr++];
    a->values[anr++] = b->values[bnr++];
    a->values[anr] = b->values[bnr];
}
void vectorCopy_f(array_float* a, int anr, array_float*b, int bnr) {
    anr *= 3;
    bnr *= 3;
    a->values[anr++] = b->values[bnr++];
    a->values[anr++] = b->values[bnr++];
    a->values[anr] = b->values[bnr];
}

void vectorAdd_i(array_int* a, int anr, array_int* b, int bnr, double scale) {
    anr *= 3;
    bnr *= 3;
    a->values[anr++] += b->values[bnr++] * (int)scale;
    a->values[anr++] += b->values[bnr++] * (int)scale;
    a->values[anr]   += b->values[bnr]   * (int)scale;
}
void vectorAdd_d(array_double* a, int anr, array_double* b, int bnr, double scale) {
    anr *= 3;
    bnr *= 3;
    a->values[anr++] += b->values[bnr++] * scale;
    a->values[anr++] += b->values[bnr++] * scale;
    a->values[anr]   += b->values[bnr]   * scale;
}
void vectorAdd_f(array_float* a, int anr, array_float* b, int bnr, double scale) {
    anr *= 3;
    bnr *= 3;
    a->values[anr++] += b->values[bnr++] * (float)scale;
    a->values[anr++] += b->values[bnr++] * (float)scale;
    a->values[anr]   += b->values[bnr]   * (float)scale;
}

void vectorSetDiff_i(array_int* dest, int dnr,
                     array_int* a, int anr,
                     array_int* b, int bnr,
                     double scale) {
    dnr *= 3; anr *= 3; bnr *= 3;
    dest->values[dnr++] = (a->values[anr++] - b->values[bnr++]) * (int)scale;
    dest->values[dnr++] = (a->values[anr++] - b->values[bnr++]) * (int)scale;
    dest->values[dnr++] = (a->values[anr++] - b->values[bnr++]) * (int)scale;
}
void vectorSetDiff_d(array_double* dest, int dnr,
                     array_double* a, int anr,
                     array_double* b, int bnr,
                     double scale) {
    dnr *= 3; anr *= 3; bnr *= 3;
    dest->values[dnr++] = (a->values[anr++] - b->values[bnr++]) * scale;
    dest->values[dnr++] = (a->values[anr++] - b->values[bnr++]) * scale;
    dest->values[dnr++] = (a->values[anr++] - b->values[bnr++]) * scale;
}
void vectorSetDiff_f(array_float* dest, int dnr,
                     array_float* a, int anr,
                     array_float* b, int bnr,
                     double scale){
    dnr *= 3; anr *= 3; bnr *= 3;
    dest->values[dnr++] = (a->values[anr++] - b->values[bnr++]) * (float)scale;
    dest->values[dnr++] = (a->values[anr++] - b->values[bnr++]) * (float)scale;
    dest->values[dnr++] = (a->values[anr++] - b->values[bnr++]) * (float)scale;
}

int vectorLenSquare_i(array_int* a, int anr) {
    anr *= 3;
    int a0 = a->values[anr];
    int a1 = a->values[anr+1];
    int a2 = a->values[anr+2];
    return a0*a0 + a1*a1 + a2*a2;
}
double vectorLenSquare_d(array_double* a, int anr) {
    anr *= 3;
    double a0 = a->values[anr];
    double a1 = a->values[anr+1];
    double a2 = a->values[anr+2];
    return a0*a0 + a1*a1 + a2*a2;
}
float vectorLenSquare_f(array_float* a, int anr) {
    anr *= 3;
    float a0 = a->values[anr];
    float a1 = a->values[anr+1];
    float a2 = a->values[anr+2];
    return a0*a0 + a1*a1 + a2*a2;
}

int vecorDistSquare_i(array_int* a, int anr, array_int* b, int bnr) {
    anr *= 3;
    bnr *= 3;
    int a0 = a->values[anr] - b->values[bnr];
    int a1 = a->values[anr+1] - b->values[bnr+1];
    int a2 = a->values[anr+2] - b->values[bnr+2];
    return a0*a0 + a1*a1 + a2*a2;
}
double vecorDistSquare_d(array_double* a, int anr, array_double* b, int bnr) {
    anr *= 3;
    bnr *= 3;
    int a0 = a->values[anr] - b->values[bnr];
    int a1 = a->values[anr+1] - b->values[bnr+1];
    int a2 = a->values[anr+2] - b->values[bnr+2];
    return a0*a0 + a1*a1 + a2*a2;
}
float vecorDistSquare_f(array_float* a, int anr, array_float* b, int bnr) {
    anr *= 3;
    bnr *= 3;
    int a0 = a->values[anr] - b->values[bnr];
    int a1 = a->values[anr+1] - b->values[bnr+1];
    int a2 = a->values[anr+2] - b->values[bnr+2];
    return a0*a0 + a1*a1 + a2*a2;
}

int vecorDot_i(array_int* a, int anr, array_int* b, int bnr) {
    anr *= 3; bnr *= 3;
    return a->values[anr]*b->values[bnr] +
           a->values[anr+1]*b->values[bnr+1] +
           a->values[anr+2]*b->values[bnr+2];
}
double vecorDot_d(array_double* a, int anr, array_double* b, int bnr) {
    anr *= 3; bnr *= 3;
    return a->values[anr]*b->values[bnr] +
           a->values[anr+1]*b->values[bnr+1] +
           a->values[anr+2]*b->values[bnr+2];
}
float vecorDot_f(array_float* a, int anr, array_float* b, int bnr) {
    anr *= 3; bnr *= 3;
    return a->values[anr]*b->values[bnr] +
           a->values[anr+1]*b->values[bnr+1] +
           a->values[anr+2]*b->values[bnr+2];
}

