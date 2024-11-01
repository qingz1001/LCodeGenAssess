#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1024

typedef struct {
    int x;
    int y;
} Point;

int m, n, k;
char grid[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void dfs(int x, int y) {
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];
        if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == '.' && !visited[nx][ny]) {
            dfs(nx, ny);
        }
    }
}

int main() {
    scanf("%d %d %d", &m, &n, &k);
    for (int i = 0; i < m; i++) {
        scanf("%s", grid[i]);
    }

    // Find the number of connected components
    int componentCount = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '.' && !visited[i][j]) {
                componentCount++;
                dfs(i, j);
            }
        }
    }

    // Check if the number of components is less than or equal to k
    if (componentCount <= k) {
        // Plant bushes to create a valid maze
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '.' && visited[i][j]) {
                    grid[i][j] = 'X';
                    k--;
                    if (k == 0) {
                        break;
                    }
                }
            }
            if (k == 0) {
                break;
            }
        }
    }

    // Output the modified grid
    for (int i = 0; i < m; i++) {
        printf("%s\n", grid[i]);
    }

    return 0;
}