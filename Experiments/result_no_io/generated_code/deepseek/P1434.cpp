#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int R, C;
int map[100][100];
int dp[100][100];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int dfs(int x, int y) {
    if (dp[x][y] != -1) return dp[x][y];
    dp[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < R && ny >= 0 && ny < C && map[nx][ny] < map[x][y]) {
            dp[x][y] = MAX(dp[x][y], dfs(nx, ny) + 1);
        }
    }
    return dp[x][y];
}

int main() {
    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf("%d", &map[i][j]);
            dp[i][j] = -1;
        }
    }

    int max_length = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            max_length = MAX(max_length, dfs(i, j));
        }
    }

    printf("%d\n", max_length);
    return 0;
}