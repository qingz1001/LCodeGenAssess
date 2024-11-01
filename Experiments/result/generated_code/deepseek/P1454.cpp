#include <stdio.h>
#include <stdbool.h>

#define MAXN 100
#define MAXM 100

char grid[MAXN][MAXM];
bool visited[MAXN][MAXM];
int n, m;

int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1, -2, -2, -2, -2, -2, 0, 0, 2, 2, 2, 2, 2};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1, -2, 0, 2, -2, 2, -2, 2, -2, 0, 2, -2, 2};

void dfs(int x, int y) {
    visited[x][y] = true;
    for (int i = 0; i < 20; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == '#' && !visited[nx][ny]) {
            dfs(nx, ny);
        }
    }
}

int countPatterns() {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#' && !visited[i][j]) {
                dfs(i, j);
                count++;
            }
        }
    }
    return count;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }
    int result = countPatterns();
    printf("%d\n", result);
    return 0;
}