#include <stdio.h>

#define N 4

int main() {
    int row_sums[N], col_sums[N], diag_sums[2];
    int known[N][N] = {0};
    int i, j, k;

    // Read row sums
    for (i = 0; i < N; i++) {
        scanf("%d", &row_sums[i]);
    }

    // Read column sums
    for (i = 0; i < N; i++) {
        scanf("%d", &col_sums[i]);
    }

    // Read diagonal sums
    scanf("%d", &diag_sums[0]);
    scanf("%d", &diag_sums[1]);

    // Read known values
    for (k = 0; k < 4; k++) {
        scanf("%d %d %d", &i, &j, &known[i][j]);
    }

    // Calculate the remaining values
    int matrix[N][N] = {0};
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (known[i][j] != 0) {
                matrix[i][j] = known[i][j];
            }
        }
    }

    // Fill the matrix
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (matrix[i][j] == 0) {
                matrix[i][j] = row_sums[i] - (matrix[i][0] + matrix[i][1] + matrix[i][2] + matrix[i][3] - matrix[i][j]);
            }
        }
    }

    // Output the matrix
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}