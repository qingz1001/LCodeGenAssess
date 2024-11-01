#include <stdio.h>

int main() {
    int row_sum[4], col_sum[4];
    int diag_main = 0, diag_secondary = 0;
    int known_values[12][3];
    int M[4][4] = {0};
    int i, j, k;

    // Read row sums
    for (i = 0; i < 4; i++) {
        scanf("%d", &row_sum[i]);
    }

    // Read column sums
    for (i = 0; i < 4; i++) {
        scanf("%d", &col_sum[i]);
    }

    // Read diagonal sums
    scanf("%d %d", &diag_main, &diag_secondary);

    // Read known values
    for (i = 0; i < 12; i++) {
        scanf("%d %d %d", &known_values[i][0], &known_values[i][1], &known_values[i][2]);
        M[known_values[i][0]][known_values[i][1]] = known_values[i][2];
    }

    // Fill the rest of the matrix
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (M[i][j] == 0) {
                M[i][j] = row_sum[i] + col_sum[j] - (M[(i+1)%4][(j+1)%4] + M[(i+2)%4][(j+2)%4] + M[(i+3)%4][(j+3)%4]) / 2;
            }
        }
    }

    // Output the matrix
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }

    return 0;
}