#include <stdio.h>
#include <stdlib.h>

#define MAXN 200
#define MAXM 200

int N, M, P;
int sums[MAXN][MAXM];
int matrix[MAXN][MAXM];

void solve() {
    // Initialize the first row and first column of the matrix
    for (int i = 0; i < N; i++) {
        matrix[i][0] = 0;
    }
    for (int j = 0; j < M; j++) {
        matrix[0][j] = 0;
    }

    // Fill the matrix based on the sums
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            // Calculate the value for matrix[i][j]
            matrix[i][j] = sums[i-1][j-1] - matrix[i-1][j-1] - matrix[i-1][j] - matrix[i][j-1];
            // Ensure the value is within the range [0, P-1]
            matrix[i][j] = (matrix[i][j] + P) % P;
        }
    }

    // Output the matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d", matrix[i][j]);
            if (j < M - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main() {
    scanf("%d %d %d", &N, &M, &P);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &sums[i][j]);
        }
    }
    solve();
    return 0;
}