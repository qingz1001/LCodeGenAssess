#include <stdio.h>
#include <stdlib.h>

#define MAX(R, C) ((R) > (C) ? (R) : (C))

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestSlideDown(int** matrix, int rows, int cols) {
    if (rows == 0 || cols == 0) return 0;

    int** dp = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        dp[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            dp[i][j] = 1;
        }
    }

    int maxLength = 1;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i > 0 && matrix[i - 1][j] < matrix[i][j]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j] + 1);
            }
            if (i < rows - 1 && matrix[i + 1][j] < matrix[i][j]) {
                dp[i][j] = max(dp[i][j], dp[i + 1][j] + 1);
            }
            if (j > 0 && matrix[i][j - 1] < matrix[i][j]) {
                dp[i][j] = max(dp[i][j], dp[i][j - 1] + 1);
            }
            if (j < cols - 1 && matrix[i][j + 1] < matrix[i][j]) {
                dp[i][j] = max(dp[i][j], dp[i][j + 1] + 1);
            }
            maxLength = max(maxLength, dp[i][j]);
        }
    }

    for (int i = 0; i < rows; i++) {
        free(dp[i]);
    }
    free(dp);

    return maxLength;
}

int main() {
    int rows, cols;
    scanf("%d %d", &rows, &cols);

    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("%d\n", longestSlideDown(matrix, rows, cols));

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}