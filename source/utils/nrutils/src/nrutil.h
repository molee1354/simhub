#ifndef simhub_nrutil_h
#define simhub_nrutil_h

#define NR_END   1
#define FREE_ARG char*

typedef double*   vector;
typedef double**  matrix;

vector newVector(unsigned int size);
matrix newMatrix(unsigned int row, unsigned int col);

void printVector(vector vec);
void printMatrix(matrix mat);
#define printObj(obj) _Generic( (obj) ,\
                       vector : printVector,\
                       matrix : printMatrix) (obj)

void freeVector(vector vec);
void freeMatrix(matrix mat);
#define freeObj(obj) _Generic( (obj) ,\
                       vector : freeVector,\
                       matrix : freeMatrix) (obj)

#endif
