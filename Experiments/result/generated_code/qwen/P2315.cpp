#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int grid[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int count = 0;
    for (int i = 0; i < n - 2; i++) {
        for (int j = 0; j <= i; j++) {
            if (grid[i][j] == 1 && grid[i + 1][j] == 1 && grid[i + 2][j] == 1) {
                if (i < n - 3 && grid[i + 3][j] == 1) continue;
                if (j > 0 && grid[i][j - 1] == 1) continue;
                if (j < i && grid[i][j + 1] == 1) continue;
                if (i > 0 && j > 0 && grid[i - 1][j - 1] == 1) continue;
                if (i > 0 && j < i && grid[i - 1][j + 1] == 1) continue;
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}