#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 30

void fill(int n, int grid[MAX_SIZE][MAX_SIZE]) {
    bool visited[MAX_SIZE][MAX_SIZE] = {false};
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Helper function to perform DFS
    void dfs(int x, int y) {
        visited[x][y] = true;
        for (int i = 0; i < 4; i++) {
            int nx = x + directions[i][0];
            int ny = y + directions[i][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny] && grid[nx][ny] == 0) {
                dfs(nx, ny);
            }
        }
    }

    // Start DFS from the border
    for (int i = 0; i < n; i++) {
        if (grid[i][0] == 0) dfs(i, 0);
        if (grid[i][n-1] == 0) dfs(i, n-1);
        if (grid[0][i] == 0) dfs(0, i);
        if (grid[n-1][i] == 0) dfs(n-1, i);
    }

    // Fill the unvisited 0's with 2
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0 && !visited[i][j]) {
                grid[i][j] = 2;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int grid[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    fill(n, grid);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }

    return 0;
}