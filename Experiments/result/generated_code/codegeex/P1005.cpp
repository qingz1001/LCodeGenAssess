#include <stdio.h>

#define MAXN 81
#define MAXM 81

long long a[MAXN][MAXM];
long long dp[MAXM][MAXM][MAXM];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%lld", &a[i][j]);
        }
    }

    for (int i = 1; i <= m; i++) {
        dp[1][i][i] = a[1][i] * (1 << (m - i + 1));
    }

    for (int i = 2; i <= n; i++) {
        for (int l = 1; l <= m; l++) {
            for (int r = l; r <= m; r++) {
                dp[i][l][r] = dp[i - 1][l][r] + (a[i][l] * (1 << (m - r + 1)) + a[i][r] * (1 << (m - l + 1)));
                for (int k = l + 1; k < r; k++) {
                    dp[i][l][r] = dp[i][l][r] > dp[i - 1][l][k] + dp[i - 1][k + 1][r] ? dp[i][l][r] : dp[i - 1][l][k] + dp[i - 1][k + 1][r];
                }
            }
        }
    }

    long long max_score = 0;
    for (int l = 1; l <= m; l++) {
        for (int r = l; r <= m; r++) {
            max_score = max_score > dp[n][l][r] ? max_score : dp[n][l][r];
        }
    }

    printf("%lld\n", max_score);
    return 0;
}