#include <stdio.h>

#define SIZE 4

void printMatrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int rowSums[SIZE], colSums[SIZE], diagSums[2];
    int known[SIZE][SIZE] = {0};
    int matrix[SIZE][SIZE] = {0};

    // Read input
    for (int i = 0; i < SIZE; i++) {
        scanf("%d", &rowSums[i]);
    }
    for (int i = 0; i < SIZE; i++) {
        scanf("%d", &colSums[i]);
    }
    scanf("%d", &diagSums[0]);
    scanf("%d", &diagSums[1]);

    for (int i = 0; i < 4; i++) {
        int x, y, value;
        scanf("%d %d %d", &x, &y, &value);
        known[x][y] = 1;
        matrix[x][y] = value;
    }

    // Fill the matrix
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (known[i][j]) continue;

            // Calculate the value for matrix[i][j]
            int rowSum = rowSums[i];
            int colSum = colSums[j];
            int diagSum1 = (i == j) ? diagSums[0] : 0;
            int diagSum2 = (i + j == SIZE - 1) ? diagSums[1] : 0;

            for (int k = 0; k < SIZE; k++) {
                if (k != j) rowSum -= matrix[i][k];
                if (k != i) colSum -= matrix[k][j];
            }

            if (i == j) {
                for (int k = 0; k < SIZE; k++) {
                    if (k != i) diagSum1 -= matrix[k][k];
                }
            }

            if (i + j == SIZE - 1) {
                for (int k = 0; k < SIZE; k++) {
                    if (k != i) diagSum2 -= matrix[k][SIZE - 1 - k];
                }
            }

            matrix[i][j] = rowSum;
        }
    }

    // Print the matrix
    printMatrix(matrix);

    return 0;
}