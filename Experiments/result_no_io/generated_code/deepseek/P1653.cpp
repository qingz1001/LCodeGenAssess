#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 500

int W, L;
int grid[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];

typedef struct {
    int x, y;
} Point;

void dfs(int x, int y) {
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < L && ny >= 0 && ny < W && !visited[nx][ny] && grid[nx][ny] <= grid[x][y]) {
            dfs(nx, ny);
        }
    }
}

int main() {
    scanf("%d %d", &W, &L);
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < W; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int components = 0;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < W; j++) {
            if (!visited[i][j]) {
                dfs(i, j);
                components++;
            }
        }
    }

    printf("%d\n", components - 1);

    return 0;
}