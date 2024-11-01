#include <stdio.h>
#include <string.h>

#define MAXN 1001
#define MAXQ 1001

char grid[MAXN][MAXN];
int n, m, q;
int visited[MAXN][MAXN];
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int dfs(int x, int y, int color) {
    int count = 1;
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == color && !visited[nx][ny]) {
            count += dfs(nx, ny, color);
        }
    }
    return count;
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    for (int i = 0; i < q; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        int ans = 0;

        // Reset visited array for each query
        memset(visited, 0, sizeof(visited));

        // Count the number of distinct paint strokes needed
        for (int x = x1 - 1; x < x2; x++) {
            for (int y = y1 - 1; y < y2; y++) {
                if (!visited[x][y]) {
                    int color = grid[x][y];
                    int size = dfs(x, y, color);
                    ans++;
                }
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}