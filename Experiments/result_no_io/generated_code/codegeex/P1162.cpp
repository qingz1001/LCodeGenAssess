#include <stdio.h>
#include <stdlib.h>

void fill(int n, int matrix[n][n]) {
    int i, j;
    int visited[n][n];

    // Initialize visited matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            visited[i][j] = 0;
        }
    }

    // Function to check if a cell is on the boundary
    int isBoundary(int x, int y) {
        return x == 0 || y == 0 || x == n-1 || y == n-1;
    }

    // Depth-first search to mark all 0's that are not in the closed loop
    void dfs(int x, int y) {
        if (x < 0 || x >= n || y < 0 || y >= n || visited[x][y] || matrix[x][y] != 0) {
            return;
        }
        visited[x][y] = 1;
        if (!isBoundary(x, y)) {
            dfs(x-1, y);
            dfs(x+1, y);
            dfs(x, y-1);
            dfs(x, y+1);
        }
    }

    // Start DFS from all 0's on the boundary
    for (i = 0; i < n; i++) {
        if (matrix[0][i] == 0) dfs(0, i);
        if (matrix[n-1][i] == 0) dfs(n-1, i);
        if (matrix[i][0] == 0) dfs(i, 0);
        if (matrix[i][n-1] == 0) dfs(i, n-1);
    }

    // Fill the remaining 0's with 2
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (matrix[i][j] == 0 && !visited[i][j]) {
                matrix[i][j] = 2;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int matrix[n][n];

    // Read the matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Fill the matrix
    fill(n, matrix);

    // Print the filled matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}