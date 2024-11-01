#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500
#define INF 1000000

int N;
int field[MAX_N][MAX_N];
int dp[MAX_N][MAX_N];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int dfs(int x, int y, int visited) {
    if (visited >= N * N / 2 + N * N % 2) {
        return 0;
    }
    if (dp[x][y] != -1) {
        return dp[x][y];
    }

    int min_cost = INF;
    if (x > 0) {
        min_cost = min(min_cost, abs(field[x][y] - field[x-1][y]) + dfs(x-1, y, visited + 1));
    }
    if (x < N-1) {
        min_cost = min(min_cost, abs(field[x][y] - field[x+1][y]) + dfs(x+1, y, visited + 1));
    }
    if (y > 0) {
        min_cost = min(min_cost, abs(field[x][y] - field[x][y-1]) + dfs(x, y-1, visited + 1));
    }
    if (y < N-1) {
        min_cost = min(min_cost, abs(field[x][y] - field[x][y+1]) + dfs(x, y+1, visited + 1));
    }

    dp[x][y] = min_cost;
    return min_cost;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &field[i][j]);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = -1;
        }
    }

    int min_cost = INF;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            min_cost = min(min_cost, dfs(i, j, 1));
        }
    }

    printf("%d\n", min_cost);

    return 0;
}