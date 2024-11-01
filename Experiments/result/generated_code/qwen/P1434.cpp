#include <stdio.h>
#include <stdlib.h>

#define MAXN 101

int dp[MAXN][MAXN];
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int R, C;

int dfs(int x, int y) {
    if (dp[x][y] != -1) return dp[x][y];
    int max_len = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];
        if (nx >= 0 && nx < R && ny >= 0 && ny < C && grid[nx][ny] < grid[x][y]) {
            max_len = fmax(max_len, dfs(nx, ny) + 1);
        }
    }
    dp[x][y] = max_len;
    return dp[x][y];
}

int main() {
    scanf("%d %d", &R, &C);
    int grid[MAXN][MAXN];
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf("%d", &grid[i][j]);
            dp[i][j] = -1;
        }
    }

    int max_slope = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            max_slope = fmax(max_slope, dfs(i, j));
        }
    }

    printf("%d\n", max_slope);
    return 0;
}