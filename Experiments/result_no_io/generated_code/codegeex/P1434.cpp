#include <stdio.h>
#include <string.h>

int R, C;
int heights[101][101];
int dp[101][101];
int maxSlide;

int max(int a, int b) {
    return a > b ? a : b;
}

void dfs(int x, int y) {
    if (dp[x][y] != 0) {
        return;
    }
    dp[x][y] = 1;
    if (x > 1 && heights[x][y] > heights[x-1][y]) {
        dfs(x-1, y);
        dp[x][y] = max(dp[x][y], dp[x-1][y] + 1);
    }
    if (x < R && heights[x][y] > heights[x+1][y]) {
        dfs(x+1, y);
        dp[x][y] = max(dp[x][y], dp[x+1][y] + 1);
    }
    if (y > 1 && heights[x][y] > heights[x][y-1]) {
        dfs(x, y-1);
        dp[x][y] = max(dp[x][y], dp[x][y-1] + 1);
    }
    if (y < C && heights[x][y] > heights[x][y+1]) {
        dfs(x, y+1);
        dp[x][y] = max(dp[x][y], dp[x][y+1] + 1);
    }
    maxSlide = max(maxSlide, dp[x][y]);
}

int main() {
    scanf("%d %d", &R, &C);
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            scanf("%d", &heights[i][j]);
        }
    }

    memset(dp, 0, sizeof(dp));
    maxSlide = 0;

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            dfs(i, j);
        }
    }

    printf("%d\n", maxSlide);
    return 0;
}