#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5
#define MAX_M 5

int N, M, T;
int SX, SY, FX, FY;
int maze[MAX_N][MAX_M];
int visited[MAX_N][MAX_M];
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

void dfs(int x, int y, int steps) {
    if (x == FX && y == FY) {
        if (steps == T + 2) {
            printf("1\n");
            exit(0);
        }
        return;
    }
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < N && ny >= 0 && ny < M && !visited[nx][ny] && maze[nx][ny] != 1) {
            visited[nx][ny] = 1;
            dfs(nx, ny, steps + 1);
            visited[nx][ny] = 0;
        }
    }
}

int main() {
    scanf("%d %d %d", &N, &M, &T);
    scanf("%d %d %d %d", &SX, &SY, &FX, &FY);
    for (int i = 0; i < T; i++) {
        int bx, by;
        scanf("%d %d", &bx, &by);
        maze[bx - 1][by - 1] = 1;
    }
    visited[SX - 1][SY - 1] = 1;
    dfs(SX - 1, SY - 1, 1);
    printf("0\n");
    return 0;
}