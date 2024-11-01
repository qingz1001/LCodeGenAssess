#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int n;
int grid[9][9];
int dp[9][9][1 << 9];

int max(int a, int b) {
    return a > b ? a : b;
}

int dfs(int x, int y, int mask) {
    if (dp[x][y][mask] != INT_MIN) return dp[x][y][mask];
    
    int res = grid[x][y];
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) continue;
        if (i == x || i == x - 1 || i == x + 1) {
            if (i == x - 1 && y == 0) continue;
            if (i == x + 1 && y == n - 1) continue;
            res = max(res, dfs(i, y, mask | (1 << i)) + grid[x][y]);
        }
    }
    return dp[x][y][mask] = res;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int maxSurvival = INT_MIN;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int mask = 0; mask < (1 << n); mask++) {
                for (int k = 0; k < n; k++) {
                    dp[k][j][mask] = INT_MIN;
                }
            }
            maxSurvival = max(maxSurvival, dfs(i, j, 1 << i));
        }
    }

    printf("%d\n", maxSurvival);
    return 0;
}