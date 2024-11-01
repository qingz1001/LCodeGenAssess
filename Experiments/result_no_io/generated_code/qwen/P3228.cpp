#include <stdio.h>

int main() {
    long long N, K, M, P;
    scanf("%lld %lld %lld %lld", &N, &K, &M, &P);

    if (K == 1) {
        printf("%lld\n", N);
        return 0;
    }

    long long dp[K + 1][N + 1];
    for (long long i = 0; i <= K; i++) {
        for (long long j = 0; j <= N; j++) {
            dp[i][j] = 0;
        }
    }

    dp[1][1] = 1;
    for (long long i = 2; i <= K; i++) {
        for (long long j = 1; j <= N; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j > 1 && j - 1 >= M * (i - 1)) {
                dp[i][j] += dp[i - 1][j - M * (i - 1)];
                dp[i][j] %= P;
            }
        }
    }

    long long result = 0;
    for (long long j = 1; j <= N; j++) {
        result += dp[K][j];
        result %= P;
    }

    printf("%lld\n", result);

    return 0;
}