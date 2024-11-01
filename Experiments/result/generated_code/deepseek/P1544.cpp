#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100
#define MAXK 5050

long long pyramid[MAXN][MAXN];
long long dp[MAXN][MAXN][MAXK];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%lld", &pyramid[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            for (int m = 0; m <= k; m++) {
                dp[i][j][m] = LLONG_MIN;
            }
        }
    }

    dp[0][0][0] = pyramid[0][0];

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            for (int m = 0; m <= k; m++) {
                if (j > 0 && dp[i-1][j-1][m] != LLONG_MIN) {
                    dp[i][j][m] = dp[i-1][j-1][m] + pyramid[i][j];
                }
                if (j < i && dp[i-1][j][m] != LLONG_MIN) {
                    dp[i][j][m] = (dp[i][j][m] == LLONG_MIN) ? dp[i-1][j][m] + pyramid[i][j] :
                                                            (dp[i-1][j][m] + pyramid[i][j] > dp[i][j][m] ? dp[i-1][j][m] + pyramid[i][j] : dp[i][j][m]);
                }
                if (m > 0) {
                    if (j > 0 && dp[i-1][j-1][m-1] != LLONG_MIN) {
                        dp[i][j][m] = (dp[i][j][m] == LLONG_MIN) ? dp[i-1][j-1][m-1] + 3 * pyramid[i][j] :
                                                                (dp[i-1][j-1][m-1] + 3 * pyramid[i][j] > dp[i][j][m] ? dp[i-1][j-1][m-1] + 3 * pyramid[i][j] : dp[i][j][m]);
                    }
                    if (j < i && dp[i-1][j][m-1] != LLONG_MIN) {
                        dp[i][j][m] = (dp[i][j][m] == LLONG_MIN) ? dp[i-1][j][m-1] + 3 * pyramid[i][j] :
                                                                (dp[i-1][j][m-1] + 3 * pyramid[i][j] > dp[i][j][m] ? dp[i-1][j][m-1] + 3 * pyramid[i][j] : dp[i][j][m]);
                    }
                }
            }
        }
    }

    long long max_score = LLONG_MIN;
    for (int j = 0; j < n; j++) {
        for (int m = 0; m <= k; m++) {
            if (dp[n-1][j][m] > max_score) {
                max_score = dp[n-1][j][m];
            }
        }
    }

    printf("%lld\n", max_score);

    return 0;
}