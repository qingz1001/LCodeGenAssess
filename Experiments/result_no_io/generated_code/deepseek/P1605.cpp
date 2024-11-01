#include <stdio.h>

#define MAXN 5
#define MAXM 5

int N, M, T;
int SX, SY, FX, FY;
int obstacles[MAXN][MAXM];
int visited[MAXN][MAXM];
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int count = 0;

void dfs(int x, int y) {
    if (x == FX - 1 && y == FY - 1) {
        count++;
        return;
    }

    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];
        if (nx >= 0 && nx < N && ny >= 0 && ny < M && !visited[nx][ny] && !obstacles[nx][ny]) {
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
        obstacles[x - 1][y - 1] = 1;
    }

    dfs(SX - 1, SY - 1);
    printf("%d\n", count);

    return 0;
}