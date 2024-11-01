#include <stdio.h>

int main() {
    int rows[4], cols[4], diag[2], matrix[4][4];
    int sumRows[4] = {0}, sumCols[4] = {0}, sumDiag[2] = {0};

    // Read input values
    scanf("%d %d %d %d %d %d %d %d %d %d %d %d", rows, rows + 1, rows + 2, rows + 3, cols, cols + 1, cols + 2, cols + 3, diag, diag + 1, matrix[0], matrix[1], matrix[2]);

    // Read the remaining 12 known positions
    for (int i = 3; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            scanf("%d %d %d", &i, &j, &matrix[i][j]);
        }
    }

    // Calculate the sum of known values for rows, columns, and diagonals
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            sumRows[i] += matrix[i][j];
            sumCols[j] += matrix[i][j];
            if (i == j) sumDiag[0] += matrix[i][j];
            if (i + j == 3) sumDiag[1] += matrix[i][j];
        }
    }

    // Calculate the unknown values
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (matrix[i][j] == 0) {
                matrix[i][j] = rows[i] - sumRows[i];
                matrix[i][j] = cols[j] - sumCols[j];
                if (i == j) matrix[i][j] = diag[0] - sumDiag[0];
                if (i + j == 3) matrix[i][j] = diag[1] - sumDiag[1];
            }
        }
    }

    // Print the result
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}