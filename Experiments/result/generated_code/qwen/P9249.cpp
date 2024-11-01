#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    long long **dp = (long long **)malloc(n * sizeof(long long *));
    for (int i = 0; i < n; i++) {
        dp[i] = (long long *)calloc(m + 1, sizeof(long long));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int edges;
            scanf("%d", &edges);
            for (int k = 1; k <= edges; k++) {
                dp[i][k] += 1;
                dp[i][k] %= MOD;
            }
        }
    }

    for (int k = 2; k <= m; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][k] = (dp[i][k] + dp[j][k - 1]) % MOD;
            }
        }
    }

    long long result = 0;
    for (int y = 0; y < n; y++) {
        for (int x = 1; x <= m; x++) {
            for (int i = 0; i < n; i++) {
                if ((i & y) == y) {
                    result = (result ^ dp[i][x]) % MOD;
                }
            }
        }
    }

    printf("%lld\n", result);

    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    return 0;
}