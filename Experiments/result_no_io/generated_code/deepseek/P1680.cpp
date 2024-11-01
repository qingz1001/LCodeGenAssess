#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

long long dp[1000001];
int c[1000001];

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &c[i]);
    }

    dp[0] = 1;
    for (int i = 1; i <= N; i++) {
        dp[i] = 0;
        for (int j = 0; j < M; j++) {
            if (i >= c[j] + 1) {
                dp[i] = (dp[i] + dp[i - (c[j] + 1)]) % MOD;
            }
        }
    }

    printf("%lld\n", dp[N]);
    return 0;
}