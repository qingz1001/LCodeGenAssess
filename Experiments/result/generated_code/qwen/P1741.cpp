#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    char grid[890][890];
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            scanf(" %c", &grid[i][j]);
        }
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            if (grid[i][j] == '!' && grid[n + i][j] == '!' &&
                grid[i][n - 1 - j] == '!' && grid[n + i][n - 1 - j] == '!') {
                count++;
            }
        }
    }

    printf("%d\n", count);

    return 0;
}