#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 998244353

typedef long long ll;

int n, m;
ll A[64][64];
ll dp[20001][64][64];

ll solve() {
    ll result = 0;

    // Initialize dp array
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[1][i][i & j] = (dp[1][i][i & j] + A[i][j]) % MOD;
        }
    }

    // Fill dp array
    for (int step = 2; step <= m; step++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    dp[step][i][j & k] = (dp[step][i][j & k] + dp[step - 1][i][j] * A[j][k]) % MOD;
                }
            }
        }
    }

    // Calculate the result
    for (int step = 1; step <= m; step++) {
        for (int i = 0; i < n; i++) {
            result ^= dp[step][i][i];
        }
    }

    return result;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lld", &A[i][j]);
        }
    }

    printf("%lld\n", solve());

    return 0;
}