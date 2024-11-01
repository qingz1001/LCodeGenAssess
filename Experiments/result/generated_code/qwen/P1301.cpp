#include <stdio.h>
#include <stdlib.h>

#define MAXN 100
#define INF 999999

int N, M;
int grid[MAXN][MAXN];
int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
int dp[MAXN][MAXN][8];

int min(int a, int b) {
    return a < b ? a : b;
}

int dfs(int x, int y, int dir) {
    if (x == N && y == M) return 0;
    if (dp[x][y][dir] != -1) return dp[x][y][dir];

    int min_steps = INF;
    for (int i = 0; i < 8; i++) {
        if (i == dir) continue;
        int nx = x + directions[i][0] * grid[x][y];
        int ny = y + directions[i][1] * grid[x][y];
        if (nx >= 1 && nx <= N && ny >= 1 && ny <= M) {
            min_steps = min(min_steps, 1 + dfs(nx, ny, i));
        }
    }

    dp[x][y][dir] = min_steps;
    return dp[x][y][dir];
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            for (int k = 0; k < 8; k++) {
                dp[i][j][k] = -1;
            }
        }
    }

    int result = dfs(1, 1, -1);
    if (result == INF) printf("NEVER\n");
    else printf("%d\n", result);

    return 0;
}