#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    char grid[990][990];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * i + 1; j++) {
            scanf(" %c", &grid[i][j]);
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < 2 * (n - i); j++) {
            scanf(" %c", &grid[i][j]);
        }
    }

    long long count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * i + 1; j++) {
            if (grid[i][j] == '!') continue;
            for (int k = i + 1; k < n; k++) {
                if (grid[k][j] == '!') continue;
                for (int l = j + 1; l < 2 * k + 1; l++) {
                    if (grid[i][l] == '!' || grid[k][l] == '!') continue;
                    if (grid[i][l] != grid[k][l]) continue;
                    count++;
                }
            }
        }
    }

    printf("%lld\n", count);

    return 0;
}