#include <stdio.h>

#define MAX_N 1001

int n, m;
char maze[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];

void dfs(int x, int y) {
    static int dx[4] = {0, 0, 1, -1};
    static int dy[4] = {1, -1, 0, 0};
    int i, nx, ny;

    for (i = 0; i < 4; i++) {
        nx = x + dx[i];
        ny = y + dy[i];
        if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny] && ((maze[x][y] == '0' && maze[nx][ny] == '1') || (maze[x][y] == '1' && maze[nx][ny] == '0'))) {
            visited[nx][ny] = 1;
            dfs(nx, ny);
        }
    }
}

int main() {
    int i, j, x, y;
    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++) {
        scanf("%s", maze[i]);
    }
    while (m--) {
        scanf("%d%d", &x, &y);
        x--; y--; // Convert to 0-based index
        if (!visited[x][y]) {
            visited[x][y] = 1;
            dfs(x, y);
        }
        printf("%d\n", visited[x][y]);
    }
    return 0;
}