#include <stdio.h>
#include <stdlib.h>

#define MAX_M 20
#define MAX_N 20
#define MAX_K 1000

int M, N, K;
int花生[MAX_M][MAX_N];
int visited[MAX_M][MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

int dfs(int x, int y, int time_left) {
    if (x < 0 || x >= M || y < 0 || y >= N || time_left <= 0 || visited[x][y]) {
        return 0;
    }
    visited[x][y] = 1;
    int result = 花生[x][y];
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            result = max(result, dfs(x + dx, y + dy, time_left - 1));
        }
    }
    visited[x][y] = 0;
    return result;
}

int main() {
    scanf("%d %d %d", &M, &N, &K);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &花生[i][j]);
        }
    }

    int max_peanuts = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            max_peanuts = max(max_peanuts, dfs(i, j, K));
        }
    }

    printf("%d\n", max_peanuts);

    return 0;
}