#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1024

char grid[MAXN][MAXN];
int m, n, k;
int visited[MAXN][MAXN];

void dfs(int x, int y) {
    if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != '.' || visited[x][y]) return;
    visited[x][y] = 1;
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

int count_spaces() {
    int count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '.') count++;
        }
    }
    return count;
}

int main() {
    scanf("%d %d %d", &m, &n, &k);
    for (int i = 0; i < m; i++) {
        scanf("%s", grid[i]);
    }

    int spaces = count_spaces();
    if (spaces < k) {
        printf("No solution\n");
        return 0;
    }

    int placed = 0;
    for (int i = 0; i < m && placed < k; i++) {
        for (int j = 0; j < n && placed < k; j++) {
            if (grid[i][j] == '.') {
                memset(visited, 0, sizeof(visited));
                dfs(i, j);
                int neighbors = 0;
                for (int dx = -1; dx <= 1; dx += 2) {
                    int nx = i + dx;
                    if (nx >= 0 && nx < m && visited[nx][j]) neighbors++;
                }
                for (int dy = -1; dy <= 1; dy += 2) {
                    int ny = j + dy;
                    if (ny >= 0 && ny < n && visited[i][ny]) neighbors++;
                }
                if (neighbors == 1) {
                    grid[i][j] = 'X';
                    placed++;
                }
            }
        }
    }

    for (int i = 0; i < m; i++) {
        printf("%s\n", grid[i]);
    }

    return 0;
}