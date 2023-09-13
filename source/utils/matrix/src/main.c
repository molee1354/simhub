#include "matrix_commonincl.h"

#define NROW 10
#define NCOL 10

int checkMethods(void) {
    double** nMatrix = (double**)malloc(sizeof(double*)*NROW);
    for (int i=0; i<NROW; i++) {
        nMatrix[i] = (double*)malloc(sizeof(double)*NCOL);
    }
    int n = 1;
    for (int i=0; i<NROW; i++) {
        for (int j=0; j<NCOL; j++) {
            nMatrix[i][j] = n++; } }

    // Matrix* myMatrix = toMatrix(nMatrix, NROW, NCOL);
    // Matrix* myMatrix = ones(NROW, NCOL);

    Matrix* myMatrix = ones(NROW, NCOL);
    Matrix* hisMatrix = toMatrix(nMatrix, NROW, NCOL);
    double** modMatrix = makeModifiable(myMatrix);

    double targ = -1.;
    modMatrix[2][2] = targ;

    double** hisMatrix_mod = makeModifiable(hisMatrix);
    hisMatrix_mod[1][0] = -4.;
    hisMatrix_mod[3][2] = -3.;
    puts("\nprintMatrix()");
    printObj(hisMatrix);

    puts("\nswapRows(mat, 0,1)");
    swapRows(hisMatrix, 0,1);
    printObj(hisMatrix);

    puts("\nswapCols(mat, 1,2)");
    swapCols(hisMatrix, 1,2);
    printObj(hisMatrix);

    puts("\ngetSlice(mat, 1,3, 1,3)");
    Matrix* slicedMat = getSlice(hisMatrix, 1,3, 1,3);
    printObj(slicedMat);

    /* puts("\nrref(mat)");
    Matrix* matRref = rref(hisMatrix);
    printObj(matRref); */

    puts("\ninvert(mat)");
    Matrix* inverted = invert(hisMatrix);
    printObj(inverted);

    double hisMatrix_det = determinant(hisMatrix);
    printf("\ndeterminant: %.2f", hisMatrix_det);

    puts("\ngetVector(0,:)");
    Vector* oneRow = getVector(inverted, 0,ALL);
    printObj(oneRow);
    puts("\ngetVector(:,1)");
    Vector* oneCol = getVector(inverted, ALL,1);
    printObj(oneCol);

    puts("\nprintMatrix()");
    printMatrix(myMatrix);

    int* matIdx = findIndex(myMatrix, targ);
    printf("\nfindIndex_v for targ %.2f = [%d, %d]\n", targ,
            matIdx[0], matIdx[1]);
    free(matIdx);

    puts("\ngetSize()");
    int* size = getSize(myMatrix);
    printf("size : [");
    printf("%d, ", size[0]);
    printf("%d]\n", size[1]);

    Matrix* matMultC = mult(myMatrix, 13.);
    Matrix* matMinus = minus(myMatrix, hisMatrix);
    Matrix* matMultE = multElem(myMatrix, matMinus);
    Matrix* matSum = plus(myMatrix, hisMatrix);
    Matrix* matMultMM = mult(hisMatrix, matMultC);

    puts("\nmatrix const mult");
    printMatrix(matMultC);
    puts("\nmatrix element-wise mult");
    printMatrix(matMultE);

    puts("\nmatrix mult MM");
    printMatrix(hisMatrix);
    printMatrix(matMultC);
    printMatrix(matMultMM);

    puts("\nmatrix sum");
    printMatrix(matSum);
    puts("\nmatrix minus");
    printMatrix(matMinus);

    // matrix mult
    puts("\nmatrix mult Vec");
    Vector* vec2 = ones(3, COL);
    Matrix* mat2 = ones(3, 3);
    Matrix* mat3 = mult(mat2, 3.);
    Vector* matMultMV = mult(mat2, vec2);
    printVector(matMultMV);

    /*double* nVector = (double*)malloc(sizeof(double)*NCOL);
    for (int i=0; i<NCOL; i++) nVector[i] = i+1; */

    // Vector* myVector = toVector(nVector, NCOL, ROW);
    Vector* myVector = zeros(NCOL, ROW);
    Vector* onesVector = ones(NCOL, ROW);
    puts("\nprintVector() zeros");
    double* modVector = makeModifiable(myVector);
    double* modVectorOnes = makeModifiable(onesVector);
    modVector[1] = targ;
    printVector(myVector);

    modVector = modVectorOnes;
    for (int i = 0; i < NCOL; i++) {
        printf("%g ", modVector[i]);
    }

    puts("\nprintVector() ones");
    printVector(onesVector);

    puts("\nVector sum");
    Vector* vecSum = plus(myVector, onesVector);
    printVector(vecSum);
    freeObj(vecSum);

    int vecIdx = findIndex(myVector, targ);
    printf("\nfindIndex_v for targ %.2f = %d\n", targ, vecIdx);

    puts("\nmatRepr()");
    matRepr(matMinus);

    puts("\nfreeVector");
    freeAll_V(myVector, onesVector, vec2, matMultMV, oneRow, oneCol,
              NULL);
    puts("\nfreematrix");
    freeAll_M(myMatrix, matSum, matMinus, hisMatrix, matMultC, matMultE,
              matMultMM, mat2, mat3,
              inverted,
              slicedMat,
              // matRref,
              NULL);

    puts("\nArgerror");
    argError();

    return 0;
}

int main() {
    puts("\narray.h called");
    puts("\nCall the \"checkMethods()\" function to check different matrix methods");
    checkMethods();
    return 0;
}
