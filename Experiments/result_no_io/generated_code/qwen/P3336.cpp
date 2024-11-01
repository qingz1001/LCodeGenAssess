#include <stdio.h>
#include <stdlib.h>

#define MOD 19940417

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    if (K == 0) {
        printf("1 %d\n", N);
        return 0;
    }

    long long dp[K + 1][N + 1];
    for (int i = 0; i <= K; i++) {
        for (int j = 0; j <= N; j++) {
            dp[i][j] = 0;
        }
    }

    dp[0][0] = 1;

    for (int k = 1; k <= K; k++) {
        for (int i = 0; i <= N; i++) {
            dp[k][i] = (dp[k][i] + dp[k - 1][i]) % MOD;
            if (i > 0) {
                dp[k][i] = (dp[k][i] + dp[k - 1][i - 1]) % MOD;
            }
        }
    }

    long long max_value = 0;
    for (int i = 0; i <= N; i++) {
        max_value = (max_value + dp[K][i]) % MOD;
    }

    printf("%lld %lld\n", dp[K][0], max_value);

    return 0;
}