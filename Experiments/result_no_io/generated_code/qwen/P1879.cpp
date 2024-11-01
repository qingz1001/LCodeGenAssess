#include <stdio.h>
#include <stdlib.h>

#define MOD 100000000

int M, N;
int grid[13][13];
int dp[14][1 << 13];

int dfs(int x, int y, int mask) {
    if (x == M) return 1;
    if (y == N) return dfs(x + 1, 0, mask);
    if (dp[x][mask] != -1) return dp[x][mask];

    int res = 0;
    if (grid[x][y] == 0 || !(mask & (1 << y))) {
        res += dfs(x, y + 1, mask);
        res %= MOD;
    }
    res += dfs(x, y + 1, mask | (1 << y));
    res %= MOD;

    return dp[x][mask] = res;
}

int main() {
    scanf("%d %d", &M, &N);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    for (int i = 0; i <= M; i++) {
        for (int j = 0; j < (1 << N); j++) {
            dp[i][j] = -1;
        }
    }

    printf("%d\n", dfs(0, 0, 0));

    return 0;
}