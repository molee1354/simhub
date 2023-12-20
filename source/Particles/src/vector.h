#ifndef simhub_particles_vector_h
#define simhub_particles_vector_h

#ifdef NAME_MANGLE
#include "array_array.h"
#else
#include "../../utils/array/src/array.h"
#endif

void vectorScale_i(array_int* a, int anr, double scale);
void vectorScale_d(array_double* a, int anr, double scale);
void vectorScale_f(array_float* a, int anr, double scale);
#define vectorScale(array, anr, scale) _Generic( (array), \
                         array_int* : vectorScale_i, \
                       array_float* : vectorScale_f, \
                      array_double* : vectorScale_d ) (array, anr, scale)

void vectorCopy_i(array_int* a, int anr, array_int*b, int bnr);
void vectorCopy_d(array_double* a, int anr, array_double*b, int bnr);
void vectorCopy_f(array_float* a, int anr, array_float*b, int bnr);
#define vectorCopy(a, anr, b, bnr) _Generic( (a), \
                         array_int* : vectorCopy_i, \
                       array_float* : vectorCopy_f, \
                      array_double* : vectorCopy_d ) (a, anr, b, bnr)

void vectorAdd_i(array_int* a, int anr, array_int* b, int bnr, double scale);
void vectorAdd_d(array_double* a, int anr, array_double* b, int bnr, double scale);
void vectorAdd_f(array_float* a, int anr, array_float* b, int bnr, double scale);
#define vectorAdd(a, anr, b, bnr, scale) _Generic( (a), \
                         array_int* : vectorAdd_i, \
                       array_float* : vectorAdd_f, \
                      array_double* : vectorAdd_d ) (a, anr, b, bnr, scale)

void vectorSetDiff_i(array_int* dest, int dnr,
                     array_int* a, int anr,
                     array_int* b, int bnr,
                     double scale);
void vectorSetDiff_d(array_double* dest, int dnr,
                     array_double* a, int anr,
                     array_double* b, int bnr,
                     double scale);
void vectorSetDiff_f(array_float* dest, int dnr,
                     array_float* a, int anr,
                     array_float* b, int bnr,
                     double scale);
#define vectorSetDiff(dest, dnr, a, anr, b, bnr, scale) _Generic( (dest), \
                         array_int* : vectorSetDiff_i, \
                       array_float* : vectorSetDiff_f, \
                      array_double* : vectorSetDiff_d \
                      ) (dest, dnr, a, anr, b, bnr, scale)

int vectorLenSquare_i(array_int* a, int anr);
double vectorLenSquare_d(array_double* a, int anr);
float vectorLenSquare_f(array_float* a, int anr);
#define vectorLenSquare(array, anr) _Generic( (array), \
                         array_int* : vectorLenSquare_i, \
                       array_float* : vectorLenSquare_f, \
                      array_double* : vectorLenSquare_d ) (array, anr)

int vectorDistSquare_i(array_int* a, int anr, array_int* b, int bnr);
double vectorDistSquare_d(array_double* a, int anr, array_double* b, int bnr);
float vectorDistSquare_f(array_float* a, int anr, array_float* b, int bnr);
#define vectorDistSquare(a, anr, b, bnr) _Generic( (a), \
                         array_int* : vectorDistSquare_i, \
                       array_float* : vectorDistSquare_f, \
                      array_double* : vectorDistSquare_d ) (a, anr, b, bnr)

int vectorDot_i(array_int* a, int anr, array_int* b, int bnr);
double vectorDot_d(array_double* a, int anr, array_double* b, int bnr);
float vectorDot_f(array_float* a, int anr, array_float* b, int bnr);
#define vectorDot(a, anr, b, bnr) _Generic( (a), \
                         array_int* : vectorDot_i, \
                       array_float* : vectorDot_f, \
                      array_double* : vectorDot_d ) (a, anr, b, bnr)

#endif
