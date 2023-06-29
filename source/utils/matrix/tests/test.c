#include <stdio.h>
#include <stdlib.h>

#include "minunit.h"
#include "test.h"

#include "../src/matrix.h"
#include "../src/guard.h"

static int testRowNum;
static int testColNum;

static const double constMultiplier = 3.;

static double testMat[N][N] = {
    {4., -3., 5.},
    {3., 4., 0.},
    {-1., 2., 3.}
};
static double testMatSliced[N][2] = {
    {-3., 5.},
    { 4., 0.},
    { 2., 3.}
};
static double testMatInv[N][N] = {
    { 0.096, 0.152, -0.16},
    {-0.072, 0.136,  0.12},
    { 0.08, -0.04,   0.2}
};
static double testMatMult[N][N] = {
    {6., 6., 6.},
    {7., 7., 7.},
    {4., 4., 4.}
};

static double testMatDet = 125.;

static double testMatOnes[N][N] = {
    {1., 1., 1.},
    {1., 1., 1.},
    {1., 1., 1.}
};
static double testMatZeros[N][N] = {
    {0., 0., 0.},
    {0., 0., 0.},
    {0., 0., 0.}
};
static double testMatEye[N][N] = {
    {1., 0., 0.},
    {0., 1., 0.},
    {0., 0., 1.}
};

void test_setup(void) {
    testRowNum = N;
    testColNum = N;
}

void test_teardown(void) {/* None */}


double** fromStatic(double staticMat[][N], int nRows, int nCols) {
    double** out = (double**)malloc(nRows*sizeof(double*));
    if (out==NULL) return NULL;
    for (int i = 0; i<nCols; i++) {
        out[i] = (double*)malloc(nCols*sizeof(double));
        if (out[i]==NULL) return NULL;
    }
    for (int i = 0; i<nCols; i++) {
        for (int j = 0; j<nRows; j++) {
            out[i][j] = staticMat[i][j];
        }
    }
    return out;
}

void freeDouble(double** dynamicMat, int nRows) {
    for (int i = 0; i<nRows; i++) {
        puts("done");
        free(dynamicMat[i]);
        dynamicMat[i] = NULL;
    }
    free(dynamicMat);
    dynamicMat = NULL;
}

MU_TEST(test_makeMatrix) {
    Matrix* testMatObj = makeMatrix(N, N);
    mu_assert_int_eq(N, testMatObj->nRows);
    mu_assert_int_eq(N, testMatObj->nCols);
    for (int i = 0; i < testMatObj->nRows; i++) {
        for (int j = 0; j < testMatObj->nCols; j++) {
            mu_assert_double_eq(0., testMatObj->e[i][j]);
        }
    }
    freeMatrix(testMatObj);
}

MU_TEST(test_toMatrix) {
    double** testMatInput = fromStatic(testMat, N, N);
    Matrix* testMatObj = toMatrix(testMatInput, N, N);
    mu_assert_int_eq(N, testMatObj->nRows);
    mu_assert_int_eq(N, testMatObj->nCols);
    for (int i = 0; i < testMatObj->nRows; i++) {
        for (int j = 0; j < testMatObj->nCols; j++) {
            mu_assert_double_eq(testMat[i][j], testMatObj->e[i][j]);
        }
    }
    // frees the double pointer along
    freeMatrix(testMatObj);
}

MU_TEST(test_zeros) {
    Matrix* testMatObj = zeros(N, N);
    mu_assert_int_eq(N, testMatObj->nRows);
    mu_assert_int_eq(N, testMatObj->nCols);
    for (int i = 0; i < testMatObj->nRows; i++) {
        for (int j = 0; j < testMatObj->nCols; j++) {
            mu_assert_double_eq(testMatZeros[i][j], testMatObj->e[i][j]);
        }
    }
    freeMatrix(testMatObj);
}

MU_TEST(test_ones) {
    Matrix* testMatObj = ones(N, N);
    mu_assert_int_eq(N, testMatObj->nRows);
    mu_assert_int_eq(N, testMatObj->nCols);
    for (int i = 0; i < testMatObj->nRows; i++) {
        for (int j = 0; j < testMatObj->nCols; j++) {
            mu_assert_double_eq(testMatOnes[i][j], testMatObj->e[i][j]);
        }
    }
    freeMatrix(testMatObj);
}

MU_TEST(test_eye) {
    Matrix* testMatObj = eye(N);
    mu_assert_int_eq(N, testMatObj->nRows);
    mu_assert_int_eq(N, testMatObj->nCols);
    for (int i = 0; i < testMatObj->nRows; i++) {
        for (int j = 0; j < testMatObj->nCols; j++) {
            mu_assert_double_eq(testMatEye[i][j], testMatObj->e[i][j]);
        }
    }
    freeMatrix(testMatObj);
}

MU_TEST(test_invert) {
    double** testMatInput = fromStatic(testMat, N, N);
    Matrix* testMatObj = toMatrix(testMatInput, N, N);
    Matrix* testMatObjInv = invert(testMatObj);
    mu_assert_int_eq(N, testMatObj->nRows);
    mu_assert_int_eq(N, testMatObj->nCols);
    for (int i = 0; i < testMatObj->nRows; i++) {
        for (int j = 0; j < testMatObj->nCols; j++) {
            mu_assert_double_eq(testMatInv[i][j], testMatObjInv->e[i][j]);
        }
    }
    // frees the double pointer along
    freeMatrix(testMatObj);
    freeMatrix(testMatObjInv);
}

MU_TEST(test_determinant) {
    double** testMatInput = fromStatic(testMat, N, N);
    Matrix* testMatObj = toMatrix(testMatInput, N, N);
    double det = determinant(testMatObj);
    mu_assert_double_eq(testMatDet, det);
    // frees the double pointer along
    freeMatrix(testMatObj);
}

MU_TEST(test_constMult) {
    Matrix* testMatObj = ones(N, N);
    Matrix* testMatObjConstMult = mult(testMatObj, constMultiplier);
    mu_assert_int_eq(N, testMatObj->nRows);
    mu_assert_int_eq(N, testMatObj->nCols);
    for (int i = 0; i < testMatObj->nRows; i++) {
        for (int j = 0; j < testMatObj->nCols; j++) {
            mu_assert_double_eq(
                    testMatOnes[i][j]*constMultiplier,
                    testMatObjConstMult->e[i][j]
                    );
        }
    }
    freeMatrix(testMatObj);
    freeMatrix(testMatObjConstMult);
}

MU_TEST(test_matMult) {
    double** testMatInput = fromStatic(testMat, N, N);
    Matrix* testMatObj = toMatrix(testMatInput, N, N);
    Matrix* testMatMult1 = ones(N, N);
    Matrix* testMatObjMult = mult(testMatObj, testMatMult1);

    mu_assert_int_eq(N, testMatObjMult->nRows);
    mu_assert_int_eq(N, testMatObjMult->nCols);
    for (int i = 0; i < testMatObjMult->nRows; i++) {
        for (int j = 0; j < testMatObjMult->nCols; j++) {
            mu_assert_double_eq(
                    testMatMult[i][j],
                    testMatObjMult->e[i][j]
                    );
        }
    }
    freeMatrix(testMatObj);
    freeMatrix(testMatMult1);
    freeMatrix(testMatObjMult);
}

MU_TEST(test_plus) {
    double** testMatInput = fromStatic(testMat, N, N);
    Matrix* testMatObj = toMatrix(testMatInput, N, N);
    Matrix* testMatAdd = ones(N,N);
    Matrix* testMatObjPlus = plus(testMatObj, testMatAdd);
    mu_assert_int_eq(N, testMatObj->nRows);
    mu_assert_int_eq(N, testMatObj->nCols);
    for (int i = 0; i < testMatObj->nRows; i++) {
        for (int j = 0; j < testMatObj->nCols; j++) {
            mu_assert_double_eq(
                    testMat[i][j]+1.,
                    testMatObjPlus->e[i][j]
                    );
        }
    }
    freeMatrix(testMatObj);
    freeMatrix(testMatAdd);
    freeMatrix(testMatObjPlus);
}

MU_TEST(test_minus) {
    double** testMatInput = fromStatic(testMat, N, N);
    Matrix* testMatObj = toMatrix(testMatInput, N, N);
    Matrix* testMatMinus = ones(N,N);
    Matrix* testMatObjMinus = minus(testMatObj, testMatMinus);
    mu_assert_int_eq(N, testMatObj->nRows);
    mu_assert_int_eq(N, testMatObj->nCols);
    for (int i = 0; i < testMatObj->nRows; i++) {
        for (int j = 0; j < testMatObj->nCols; j++) {
            mu_assert_double_eq(
                    testMat[i][j]-1.,
                    testMatObjMinus->e[i][j]
                    );
        }
    }
    freeMatrix(testMatObj);
    freeMatrix(testMatMinus);
    freeMatrix(testMatObjMinus);
}

MU_TEST(test_slice) {
    double** testMatInput = fromStatic(testMat, N, N);
    Matrix* testMatObj = toMatrix(testMatInput, N, N);
    Matrix* testMatObjSlice = getSlice(testMatObj, 1,3, 0,N );

    mu_assert_int_eq(N, testMatObjSlice->nRows);
    mu_assert_int_eq(2, testMatObjSlice->nCols);
    for (int i = 0; i < testMatObjSlice->nRows; i++) {
        for (int j = 0; j < testMatObjSlice->nCols; j++) {
            mu_assert_double_eq(
                    testMatSliced[i][j],
                    testMatObjSlice->e[i][j]
                    );
        }
    }
    freeMatrix(testMatObj);
    freeMatrix(testMatObjSlice);
}


MU_TEST(test_fail) {
	mu_fail("Fail now!");
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(test_makeMatrix);
    MU_RUN_TEST(test_toMatrix);
    MU_RUN_TEST(test_zeros);
    MU_RUN_TEST(test_ones);
    MU_RUN_TEST(test_eye);
    MU_RUN_TEST(test_invert);
    MU_RUN_TEST(test_determinant);
    MU_RUN_TEST(test_matMult);
    MU_RUN_TEST(test_constMult);
    MU_RUN_TEST(test_plus);
    MU_RUN_TEST(test_minus);
    MU_RUN_TEST(test_slice);



    // MU_RUN_TEST(test_fail);
}

int main( ) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
