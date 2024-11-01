#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

long long dp[1001][1001];
int C[1001];

long long mod_add(long long a, long long b) {
    return (a + b) % MOD;
}

long long mod_mul(long long a, long long b) {
    return (a * b) % MOD;
}

void precompute() {
    for (int i = 0; i <= 1000; ++i) {
        dp[i][0] = 1;
    }
    for (int i = 1; i <= 1000; ++i) {
        for (int j = 1; j <= 1000; ++j) {
            dp[i][j] = mod_add(dp[i - 1][j], mod_mul(i, dp[i - 1][j - 1]));
        }
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; ++i) {
        scanf("%d", &C[i]);
    }

    precompute();

    long long result = 0;
    for (int i = 1; i <= N; ++i) {
        if (i > C[0]) {
            result = mod_add(result, dp[N - i][M - 1]);
        }
    }

    printf("%lld\n", result);

    return 0;
}