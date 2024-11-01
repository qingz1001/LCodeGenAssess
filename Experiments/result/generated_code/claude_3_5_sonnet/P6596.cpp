#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 51
#define MAXM 1225

long long dp[MAXN][MAXM];
long long C[MAXN][MAXN];

void init_combinations() {
    for (int i = 0; i < MAXN; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
        }
    }
}

long long pow_mod(long long base, int exp) {
    long long result = 1;
    while (exp > 0) {
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
        for (int j = 0; j <= m && j <= i*(i-1)/2; j++) {
            for (int k = 1; k < i; k++) {
                for (int l = 0; l <= j && l <= k*(i-k); l++) {
                    long long ways = (C[i-1][k-1] * dp[k][l]) % MOD;
                    ways = (ways * dp[i-k][j-l]) % MOD;
                    ways = (ways * C[k*(i-k)][l]) % MOD;
                    dp[i][j] = (dp[i][j] + ways) % MOD;
                }
            }
        }
    }

    long long result = 0;
    for (int j = 0; j <= m; j++) {
        result = (result + dp[n][j]) % MOD;
    }

    long long total = pow_mod(2, n*(n-1)/2);
    result = (total - result + MOD) % MOD;

    printf("%lld\n", result);

    return 0;
}