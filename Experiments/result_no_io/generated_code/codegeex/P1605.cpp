#include <stdio.h>

int N, M, T;
int SX, SY, FX, FY;
int maze[6][6];
int ways[6][6];

int dfs(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= M || maze[x][y] == 1) {
        return 0;
    }
    if (x == FX && y == FY) {
        return 1;
    }
    if (ways[x][y] != -1) {
        return ways[x][y];
    }
    ways[x][y] = 0;
    ways[x][y] += dfs(x + 1, y);
    ways[x][y] += dfs(x - 1, y);
    ways[x][y] += dfs(x, y + 1);
    ways[x][y] += dfs(x, y - 1);
    return ways[x][y];
}

int main() {
    scanf("%d%d%d", &N, &M, &T);
    scanf("%d%d%d%d", &SX, &SY, &FX, &FY);
    for (int i = 0; i < T; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        maze[x][y] = 1;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            ways[i][j] = -1;
        }
    }
    printf("%d\n", dfs(SX, SY));
    return 0;
}