#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000
#define MAXM 100000

int n, m;
char maze[MAXN][MAXN];
int visited[MAXN][MAXN];
int component_size[MAXN * MAXN];
int component_id[MAXN][MAXN];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void dfs(int x, int y, int id) {
    visited[x][y] = 1;
    component_id[x][y] = id;
    component_size[id]++;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny] && maze[x][y] != maze[nx][ny]) {
            dfs(nx, ny, id);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", maze[i]);
    }

    int id = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[i][j]) {
                dfs(i, j, id++);
            }
        }
    }

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--;
        printf("%d\n", component_size[component_id[x][y]]);
    }

    return 0;
}