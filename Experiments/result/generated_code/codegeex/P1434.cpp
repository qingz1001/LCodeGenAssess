#include <stdio.h>
#include <string.h>

int R, C;
int heights[100][100];
int dp[100][100];

int dfs(int x, int y) {
    if (dp[x][y] != 0) {
        return dp[x][y];
    }
    int max_length = 1;
    if (x > 0 && heights[x-1][y] < heights[x][y]) {
        max_length = fmax(max_length, 1 + dfs(x-1, y));
    }
    if (x < R-1 && heights[x+1][y] < heights[x][y]) {
        max_length = fmax(max_length, 1 + dfs(x+1, y));
    }
    if (y > 0 && heights[x][y-1] < heights[x][y]) {
        max_length = fmax(max_length, 1 + dfs(x, y-1));
    }
    if (y < C-1 && heights[x][y+1] < heights[x][y]) {
        max_length = fmax(max_length, 1 + dfs(x, y+1));
    }
    dp[x][y] = max_length;
    return max_length;
}

int main() {
    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf("%d", &heights[i][j]);
        }
    }

    memset(dp, 0, sizeof(dp));
    int max_slope = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            max_slope = fmax(max_slope, dfs(i, j));
        }
    }

    printf("%d\n", max_slope);
    return 0;
}