#include <stdio.h>
#include <stdlib.h>

#define MAXN 205
#define MAXP 11

int N, M, P;
int sum[MAXN][MAXN];

void solve() {
    int **matrix = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int *)malloc(M * sizeof(int));
    }

    // Initialize the matrix with -1 to indicate unassigned values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrix[i][j] = -1;
        }
    }

    // Fill the matrix using the given sums
    for (int i = 1; i <= N - 1; i++) {
        for (int j = 1; j <= M - 1; j++) {
            int s = sum[i][j];
            if (s == 0) continue;

            // Try to assign values to the submatrix
            for (int a = 0; a < P; a++) {
                for (int b = 0; b < P; b++) {
                    for (int c = 0; c < P; c++) {
                        int d = s - a - b - c;
                        if (d >= 0 && d < P) {
                            if (matrix[i - 1][j - 1] == -1 || matrix[i - 1][j - 1] > a) matrix[i - 1][j - 1] = a;
                            if (matrix[i - 1][j] == -1 || matrix[i - 1][j] > b) matrix[i - 1][j] = b;
                            if (matrix[i][j - 1] == -1 || matrix[i][j - 1] > c) matrix[i][j - 1] = c;
                            if (matrix[i][j] == -1 || matrix[i][j] > d) matrix[i][j] = d;
                        }
                    }
                }
            }
        }
    }

    // Print the resulting matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d", matrix[i][j]);
            if (j < M - 1) printf(" ");
        }
        printf("\n");
    }

    // Free allocated memory
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    scanf("%d %d %d", &N, &M, &P);

    // Read the sum matrix
    for (int i = 1; i <= N - 1; i++) {
        for (int j = 1; j <= M - 1; j++) {
            scanf("%d", &sum[i][j]);
        }
    }

    solve();

    return 0;
}