#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

int n, m;
char maze[MAXN][MAXN];
int visited[MAXN][MAXN];

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n || visited[x][y] || maze[x][y] == maze[0][0]) return;
    visited[x][y] = 1;
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", maze[i]);
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                visited[j][k] = 0;
            }
        }
        dfs(x, y);
        int count = 0;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (visited[j][k]) count++;
            }
        }
        printf("%d\n", count);
    }
    return 0;
}