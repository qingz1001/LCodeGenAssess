#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int matrix[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int changes = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i == 0 || i == n - 1 || j == 0 || j == n - 1) && matrix[i][j] == 0) {
                changes++;
            } else if (i > 0 && i < n - 1 && j > 0 && j < n - 1) {
                int count = 0;
                if (matrix[i - 1][j] % 2 != 0) count++;
                if (matrix[i + 1][j] % 2 != 0) count++;
                if (matrix[i][j - 1] % 2 != 0) count++;
                if (matrix[i][j + 1] % 2 != 0) count++;
                if (count % 2 != 0) {
                    changes++;
                }
            }
        }
    }

    printf("%d\n", changes);

    return 0;
}