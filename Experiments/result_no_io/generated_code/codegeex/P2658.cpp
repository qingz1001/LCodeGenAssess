#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500

int grid[MAXN][MAXN];
int visited[MAXN][MAXN];
int M, N;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

typedef struct {
    int x;
    int y;
    int diff;
} Cell;

int compare(const void *a, const void *b) {
    Cell *cellA = (Cell *)a;
    Cell *cellB = (Cell *)b;
    return cellA->diff - cellB->diff;
}

void dfs(int x, int y, int *maxDiff) {
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < M && ny >= 0 && ny < N && !visited[nx][ny]) {
            int diff = abs(grid[x][y] - grid[nx][ny]);
            if (diff > *maxDiff) {
                *maxDiff = diff;
            }
            dfs(nx, ny, maxDiff);
        }
    }
}

int findDifficulty() {
    int maxDiff = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 1) {
                dfs(i, j, &maxDiff);
            }
        }
    }
    return maxDiff;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    printf("%d\n", findDifficulty());
    return 0;
}