#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10

int N;
int grid[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];

int maxSurvival = INT_MIN;

void dfs(int x, int y, int currentSum) {
    if (x < 0 || x >= N || y < 0 || y >= N || visited[x][y]) return;
    visited[x][y] = 1;
    currentSum += grid[x][y];
    maxSurvival = (currentSum > maxSurvival) ? currentSum : maxSurvival;
    
    dfs(x + 1, y, currentSum);
    dfs(x - 1, y, currentSum);
    dfs(x, y + 1, currentSum);
    dfs(x, y - 1, currentSum);
    
    visited[x][y] = 0;
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
            dfs(i, j, 0);
        }
    }
    
    printf("%d\n", maxSurvival);
    return 0;
}