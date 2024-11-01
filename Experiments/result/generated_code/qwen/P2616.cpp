#include <stdio.h>
#include <limits.h>

#define MAX_K 100
#define MAX_N 100
#define MAX_E 350

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int K, E, N;
    scanf("%d %d %d", &K, &E, &N);

    int X[MAX_N], F[MAX_N], C[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &X[i], &F[i], &C[i]);
    }

    int dp[MAX_K + 1][MAX_E + 1];
    for (int i = 0; i <= K; i++) {
        for (int j = 0; j <= E; j++) {
            dp[i][j] = INT_MAX / 2;
        }
    }
    dp[0][0] = 0;

    for (int i = 0; i < N; i++) {
        for (int k = 0; k <= K; k++) {
            for (int j = 0; j <= E; j++) {
                if (dp[k][j] == INT_MAX / 2) continue;
                int new_k = min(k + F[i], K);
                int cost = C[i] * F[i];
                dp[new_k][j] = min(dp[new_k][j], dp[k][j] + cost);
                if (j + X[i] <= E) {
                    dp[new_k][j + X[i]] = min(dp[new_k][j + X[i]], dp[k][j] + X[i] * k);
                }
            }
        }
    }

    int ans = INT_MAX / 2;
    for (int j = 0; j <= E; j++) {
        ans = min(ans, dp[K][j]);
    }

    printf("%d\n", ans);

    return 0;
}