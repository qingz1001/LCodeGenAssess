#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1501

int n, m;
char maze[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || maze[x][y] == '#' || visited[x][y]) {
        return;
    }
    visited[x][y] = 1;
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

int main() {
    while (scanf("%d %d", &n, &m) != EOF) {
        memset(visited, 0, sizeof(visited));
        for (int i = 0; i < n; i++) {
            scanf("%s", maze[i]);
        }
        int startX, startY;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (maze[i][j] == 'S') {
                    startX = i;
                    startY = j;
                    break;
                }
            }
        }
        dfs(startX, startY);
        int flag = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (visited[i][j] && (maze[i][j] == '.' || maze[i][j] == 'S')) {
                    flag = 1;
                    break;
                }
            }
            if (flag) break;
        }
        if (flag) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}