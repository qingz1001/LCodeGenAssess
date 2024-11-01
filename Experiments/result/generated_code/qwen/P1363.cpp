#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1500
#define MAX_M 1500

char maze[MAX_N][MAX_M];
int visited[MAX_N][MAX_M];
int n, m;

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || maze[x][y] == '#' || visited[x][y]) return;
    visited[x][y] = 1;
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

int main() {
    while (scanf("%d %d", &n, &m) != EOF) {
        for (int i = 0; i < n; ++i) {
            scanf(" %s", maze[i]);
        }
        memset(visited, 0, sizeof(visited));
        int start_x, start_y;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (maze[i][j] == 'S') {
                    start_x = i;
                    start_y = j;
                    break;
                }
            }
        }
        dfs(start_x, start_y);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (!visited[i][j] && maze[i][j] == '.') {
                    printf("No\n");
                    goto next_test;
                }
            }
        }
        printf("Yes\n");
next_test:;
    }
    return 0;
}