#include <stdio.h>
#include <stdlib.h>

#define MAXN 35

void dfs(int x, int y, int n, int matrix[MAXN][MAXN], int visited[MAXN][MAXN]) {
    if (x < 0 || x >= n || y < 0 || y >= n || matrix[x][y] != 0 || visited[x][y]) return;
    visited[x][y] = 1;
    matrix[x][y] = 2;
    dfs(x + 1, y, n, matrix, visited);
    dfs(x - 1, y, n, matrix, visited);
    dfs(x, y + 1, n, matrix, visited);
    dfs(x, y - 1, n, matrix, visited);
}

int main() {
    int n;
    scanf("%d", &n);
    int matrix[MAXN][MAXN];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int visited[MAXN][MAXN] = {0};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == 1 && !visited[i][j]) {
                dfs(i, j, n, matrix, visited);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}