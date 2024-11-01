#include <stdio.h>
#include <stdlib.h>

#define MAXN 10

int N;
int grid[MAXN][MAXN];
int maxSurvival = INT_MIN;

void dfs(int x, int y, int survival, int visited[MAXN][MAXN]) {
    if (x < 0 || x >= N || y < 0 || y >= N || visited[x][y]) return;
    visited[x][y] = 1;
    survival += grid[x][y];
    if (survival > maxSurvival) {
        maxSurvival = survival;
    }
    dfs(x + 1, y, survival, visited);
    dfs(x - 1, y, survival, visited);
    dfs(x, y + 1, survival, visited);
    dfs(x, y - 1, survival, visited);
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int visited[MAXN][MAXN] = {0};
            dfs(i, j, 0, visited);
        }
    }

    printf("%d\n", maxSurvival);

    return 0;
}