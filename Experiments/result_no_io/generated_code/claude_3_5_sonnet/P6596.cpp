#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAX_N 51

long long dp[MAX_N][MAX_N * (MAX_N - 1) / 2 + 1];
long long C[MAX_N][MAX_N];

void init_combinations() {
    for (int i = 0; i < MAX_N; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
        }
    }
}

long long power(long long base, int exp) {
    long long result = 1;
    while (exp) {
        if (exp & 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return result;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    init_combinations();

    memset(dp, 0, sizeof(dp));
    dp[1][0] = 1;

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 1; k < i; k++) {
                int edges = k * (i - k);
                if (j >= edges) {
                    long long ways = (C[i-1][k-1] * dp[k][0]) % MOD;
                    ways = (ways * dp[i-k][j-edges]) % MOD;
                    dp[i][j] = (dp[i][j] + ways) % MOD;
                }
            }
        }
        for (int j = m; j >= 1; j--) {
            dp[i][j] = (dp[i][j] + dp[i][j-1]) % MOD;
        }
    }

    long long total_graphs = power(2, n * (n - 1) / 2);
    long long result = (total_graphs - dp[n][m] + MOD) % MOD;

    printf("%lld\n", result);

    return 0;
}