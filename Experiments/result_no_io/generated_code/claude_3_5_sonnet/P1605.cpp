#include <stdio.h>

#define MAX_N 5
#define MAX_M 5

int N, M, T;
int SX, SY, FX, FY;
int maze[MAX_N + 1][MAX_M + 1];
int visited[MAX_N + 1][MAX_M + 1];
int count = 0;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void dfs(int x, int y) {
    if (x == FX && y == FY) {
        count++;
        return;
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 1 && nx <= N && ny >= 1 && ny <= M && !maze[nx][ny] && !visited[nx][ny]) {
            visited[nx][ny] = 1;
            dfs(nx, ny);
            visited[nx][ny] = 0;
        }
    }
}

int main() {
    scanf("%d %d %d", &N, &M, &T);
    scanf("%d %d %d %d", &SX, &SY, &FX, &FY);

    for (int i = 0; i < T; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        maze[x][y] = 1;
    }

    visited[SX][SY] = 1;
    dfs(SX, SY);

    printf("%d\n", count);

    return 0;
}