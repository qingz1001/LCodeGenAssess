#include <stdio.h>

#define MAXN 6

int N, M, T;
int SX, SY, FX, FY;
int obstacles[MAXN][MAXN];
int visited[MAXN][MAXN];
int ways = 0;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

void dfs(int x, int y) {
    if (x == FX && y == FY) {
        ways++;
        return;
    }

    visited[x][y] = 1;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 1 && nx <= N && ny >= 1 && ny <= M && !visited[nx][ny] && !obstacles[nx][ny]) {
            dfs(nx, ny);
        }
    }

    visited[x][y] = 0;
}

int main() {
    scanf("%d %d %d", &N, &M, &T);
    scanf("%d %d %d %d", &SX, &SY, &FX, &FY);

    for (int i = 0; i < T; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        obstacles[x][y] = 1;
    }

    dfs(SX, SY);

    printf("%d\n", ways);

    return 0;
}