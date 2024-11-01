#include <stdio.h>

void dfs(int n, int m, char matrix[n][m], int i, int j) {
    if (i < 0 || i >= n || j < 0 || j >= m || matrix[i][j] == '0') {
        return;
    }
    matrix[i][j] = '0'; // Mark the cell as visited by setting it to '0'
    dfs(n, m, matrix, i - 1, j); // Up
    dfs(n, m, matrix, i + 1, j); // Down
    dfs(n, m, matrix, i, j - 1); // Left
    dfs(n, m, matrix, i, j + 1); // Right
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char matrix[n][m];

    for (int i = 0; i < n; i++) {
        scanf("%s", matrix[i]);
    }

    int cellCount = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] != '0') {
                cellCount++;
                dfs(n, m, matrix, i, j);
            }
        }
    }

    printf("%d\n", cellCount);
    return 0;
}