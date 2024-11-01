#include <stdio.h>
#include <stdlib.h>

#define MAXN 105
#define MAXK 5555

long long dp[MAXN][MAXN];
int pyramid[MAXN][MAXN];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            scanf("%d", &pyramid[i][j]);
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            dp[i][j] = -1e18;
        }
    }

    dp[1][1] = pyramid[1][1];

    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            dp[i][j] = dp[i-1][j-1] + pyramid[i][j];
            if (j > 1) {
                dp[i][j] = dp[i-1][j] + pyramid[i][j];
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            for (int l = 1; l <= k; ++l) {
                if (dp[i][j] == -1e18) continue;
                for (int m = 1; m <= i-1; ++m) {
                    for (int p = 1; p <= m; ++p) {
                        dp[m][p] = dp[m-1][p-1] + pyramid[m][p] * 3;
                        if (p > 1) {
                            dp[m][p] = dp[m-1][p] + pyramid[m][p] * 3;
                        }
                    }
                }
                for (int m = i+1; m <= n; ++m) {
                    for (int p = 1; p <= m; ++p) {
                        dp[m][p] = dp[m-1][p-1] + pyramid[m][p];
                        if (p > 1) {
                            dp[m][p] = dp[m-1][p] + pyramid[m][p];
                        }
                    }
                }
                dp[i][j] += pyramid[i][j];
            }
        }
    }

    long long max_score = -1e18;
    for (int j = 1; j <= n; ++j) {
        max_score = dp[n][j] > max_score ? dp[n][j] : max_score;
    }

    printf("%lld\n", max_score);

    return 0;
}