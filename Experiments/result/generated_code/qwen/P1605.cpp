#include <stdio.h>
#include <stdbool.h>

#define MAX_N 5
#define MAX_M 5

int N, M, T;
int SX, SY, FX, FY;
bool maze[MAX_N][MAX_M];
bool visited[MAX_N][MAX_M];

void dfs(int x, int y, int steps) {
    if (x == FX && y == FY && steps == T + 2) {
        printf("1\n");
        exit(0);
    }
    if (steps > T + 2 || x < 0 || x >= N || y < 0 || y >= M || visited[x][y] || maze[x][y]) {
        return;
    }
    visited[x][y] = true;
    dfs(x + 1, y, steps + 1);
    dfs(x - 1, y, steps + 1);
    dfs(x, y + 1, steps + 1);
    dfs(x, y - 1, steps + 1);
    visited[x][y] = false;
}

int main() {
    scanf("%d %d %d", &N, &M, &T);
    scanf("%d %d %d %d", &SX, &SY, &FX, &FY);
    for (int i = 0; i < T; i++) {
        int rx, ry;
        scanf("%d %d", &rx, &ry);
        maze[rx - 1][ry - 1] = true;
    }
    dfs(SX - 1, SY - 1, 1);
    printf("0\n");
    return 0;
}