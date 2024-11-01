#include <stdio.h>

#define MAXN 100
#define MAXM 100

int n, m;
char matrix[MAXN][MAXM];
int visited[MAXN][MAXM];

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || visited[x][y] || matrix[x][y] == '0') {
        return;
    }
    visited[x][y] = 1;
    dfs(x - 1, y);
    dfs(x + 1, y);
    dfs(x, y - 1);
    dfs(x, y + 1);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", matrix[i]);
    }

    int cellCount = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] != '0' && !visited[i][j]) {
                dfs(i, j);
                cellCount++;
            }
        }
    }

    printf("%d\n", cellCount);
    return 0;
}