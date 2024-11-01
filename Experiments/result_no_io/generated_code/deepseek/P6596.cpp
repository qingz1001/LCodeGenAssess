#include <stdio.h>
#include <stdbool.h>

#define MOD 1000000007
#define MAXN 51
#define MAXM 1276

typedef long long ll;

ll dp[MAXN][MAXM];
ll comb[MAXN][MAXN];

void precompute_combinations() {
    for (int i = 0; i < MAXN; i++) {
        comb[i][0] = comb[i][i] = 1;
        for (int j = 1; j < i; j++) {
            comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % MOD;
        }
    }
}

ll solve(int n, int m) {
    dp[1][0] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = 0;
            for (int k = 1; k < i; k++) {
                int edges = k * (i - k);
                for (int l = 0; l <= j && l <= edges; l++) {
                    dp[i][j] = (dp[i][j] + dp[k][l] * dp[i-k][j-l] % MOD * comb[i-1][k-1] % MOD) % MOD;
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
    ll result = solve(n, m);

    printf("%lld\n", result);
    return 0;
}