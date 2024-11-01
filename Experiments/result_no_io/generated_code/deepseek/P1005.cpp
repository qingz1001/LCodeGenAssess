#include <stdio.h>
#include <string.h>

#define MAXN 80
#define MAXM 80
#define MAX_SCORE 1000000000000000000LL

typedef long long ll;

ll dp[MAXM][MAXM];
ll a[MAXN][MAXM];

ll max(ll a, ll b) {
    return a > b ? a : b;
}

ll solve(int n, int m) {
    ll total_score = 0;

    for (int i = 0; i < n; i++) {
        memset(dp, 0, sizeof(dp));

        for (int len = 1; len <= m; len++) {
            for (int l = 0; l + len - 1 < m; l++) {
                int r = l + len - 1;
                ll power = 1LL << (m - len + 1);
                if (l == r) {
                    dp[l][r] = a[i][l] * power;
                } else {
                    dp[l][r] = max(dp[l + 1][r] + a[i][l] * power, dp[l][r - 1] + a[i][r] * power);
                }
            }
        }

        total_score += dp[0][m - 1];
    }

    return total_score;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%lld", &a[i][j]);
        }
    }

    printf("%lld\n", solve(n, m));

    return 0;
}