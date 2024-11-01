#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    long long **A = (long long **)malloc(n * sizeof(long long *));
    for (int i = 0; i < n; ++i) {
        A[i] = (long long *)malloc(n * sizeof(long long));
        for (int j = 0; j < n; ++j) {
            scanf("%lld", &A[i][j]);
        }
    }

    long long dp[m + 1][n];
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j] = 0;
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i <= m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i >= A[k][j]) {
                    dp[i][j] += dp[i - A[k][j]][k];
                    dp[i][j] %= MOD;
                }
            }
        }
    }

    long long result = 0;
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < n; ++j) {
            result ^= dp[i][j];
            result %= MOD;
        }
    }

    printf("%lld\n", result);

    for (int i = 0; i < n; ++i) {
        free(A[i]);
    }
    free(A);

    return 0;
}