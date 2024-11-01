#include <stdio.h>
#include <stdbool.h>

#define MOD 1000000007
#define MAXN 50

typedef long long ll;

ll dp[MAXN + 1][MAXN * (MAXN - 1) / 2 + 1];
ll comb[MAXN + 1][MAXN + 1];

void precompute_combinations() {
    for (int i = 0; i <= MAXN; i++) {
        comb[i][0] = comb[i][i] = 1;
        for (int j = 1; j < i; j++) {
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
        }
    }
}

ll solve(int n, int m) {
    dp[1][0] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = 0;
            for (int k = 0; k < i; k++) {
                for (int l = 0; l <= j; l++) {
                    if (l <= k * (i - k)) {
                        dp[i][j] = (dp[i][j] + dp[k][l] * dp[i - k][j - l] % MOD * comb[i - 1][k] % MOD) % MOD;
                    }
                }
            }
        }
    }
    return dp[n][m];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    precompute_combinations();
    printf("%lld\n", solve(n, m));

    return 0;
}