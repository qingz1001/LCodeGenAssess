#include <stdio.h>

int main() {
    int row_sums[4], col_sums[4];
    int diag_sum1, diag_sum2;
    int known_values[12][3];
    int M[4][4] = {0};

    // Read input
    for (int i = 0; i < 4; i++) scanf("%d", &row_sums[i]);
    for (int i = 0; i < 4; i++) scanf("%d", &col_sums[i]);
    scanf("%d %d", &diag_sum1, &diag_sum2);
    for (int i = 0; i < 12; i++) {
        scanf("%d %d %d", &known_values[i][0], &known_values[i][1], &known_values[i][2]);
        M[known_values[i][0]][known_values[i][1]] = known_values[i][2];
    }

    // Fill the board
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (M[i][j] == 0) {
                M[i][j] = row_sums[i] + col_sums[j] - (M[0][j] + M[1][j] + M[2][j] + M[3][j]);
                if (i == j) diag_sum1 -= M[i][j];
                if (i + j == 3) diag_sum2 -= M[i][j];
            }
        }
    }

    // Adjust the diagonal sums
    for (int i = 0; i < 4; i++) {
        M[i][i] += diag_sum1;
        M[i][3-i] += diag_sum2;
    }

    // Print the result
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }

    return 0;
}