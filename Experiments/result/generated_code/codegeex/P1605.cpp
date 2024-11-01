#include <stdio.h>

int n, m, t;
int sx, sy, fx, fy;
int maze[6][6];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int count = 0;

void dfs(int x, int y) {
    if (x == fx && y == fy) {
        count++;
        return;
    }
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && maze[nx][ny] == 0) {
            maze[nx][ny] = 1;
            dfs(nx, ny);
            maze[nx][ny] = 0;
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &t);
    scanf("%d %d %d %d", &sx, &sy, &fx, &fy);
    for (int i = 0; i < t; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        maze[a][b] = 1;
    }
    maze[sx][sy] = 1;
    dfs(sx, sy);
    printf("%d", count);
    return 0;
}