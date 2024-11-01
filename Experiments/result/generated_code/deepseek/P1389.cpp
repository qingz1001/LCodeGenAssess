#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 150
#define INF 1000000000

int N;
int V[MAXN], A[MAXN];
int dp[MAXN][MAXN];

int max(int a, int b) {
    return a > b ? a : b;
}

int dfs(int l, int r) {
    if (l > r) return 0;
    if (dp[l][r] != -INF) return dp[l][r];

    dp[l][r] = -INF;

    for (int i = l; i <= r; i++) {
        if (i > l && A[i] != A[i - 1] + 1) continue;
        if (i < r && A[i] != A[i + 1] - 1) continue;
        int score = V[i - l];
        dp[l][r] = max(dp[l][r], dfs(l, i - 1) + dfs(i + 1, r) + score);
    }

    return dp[l][r];
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &V[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = -INF;
        }
    }

    printf("%d\n", dfs(0, N - 1));

    return 0;
}