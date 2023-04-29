#include <stdio.h>

#define MAX_SIZE 100

void swap_rows(float mat[][MAX_SIZE], int i, int j, int n) {
    int k;
    float temp;
    for (k = 0; k < n; k++) {
        temp = mat[i][k];
        mat[i][k] = mat[j][k];
        mat[j][k] = temp;
    }
}

void print_matrix(float mat[][MAX_SIZE], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%f ", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    float mat[MAX_SIZE][MAX_SIZE];
    float inv[MAX_SIZE][MAX_SIZE];
    float ratio;
    int i, j, k, n;
    
    printf("Enter the order of the matrix: ");
    scanf("%d", &n);
    
    printf("Enter the elements of the matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%f", &mat[i][j]);
            if (i == j) {
                inv[i][j] = 1;
            } else {
                inv[i][j] = 0;
            }
        }
    }
    
    for (i = 0; i < n; i++) {
        if (mat[i][i] == 0) {
            for (j = i+1; j < n; j++) {
                if (mat[j][i] != 0) {
                    swap_rows(mat, i, j, n);
                    swap_rows(inv, i, j, n);
                    break;
                }
            }
            if (j == n) {
                printf("The matrix is not invertible.\n");
                return 0;
            }
        }
        for (j = 0; j < n; j++) {
            if (j != i) {
                ratio = mat[j][i] / mat[i][i];
                for (k = 0; k < n; k++) {
                    mat[j][k] -= ratio * mat[i][k];
                    inv[j][k] -= ratio * inv[i][k];
                }
            }
        }
    }
    
    for (i = 0; i < n; i++) {
        ratio = mat[i][i];
        for (j = 0; j < n; j++) {
            mat[i][j] /= ratio;
            inv[i][j] /= ratio;
        }
    }
    
    printf("The inverse of the matrix is:\n");
    print_matrix(inv, n);
    
    return 0;
}
