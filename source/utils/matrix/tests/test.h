#ifndef _test_h
#define _test_h

#define N 3

/*
 * Function to convert a static double 2d array to a dynamic 2d array
 */
double** fromStatic(double staticMat[][N], int nRows, int nCols);

/*
 * Function to free a dynamic 2d array
 */
void freeDouble(double** dynamicMat, int nRows);

#endif
