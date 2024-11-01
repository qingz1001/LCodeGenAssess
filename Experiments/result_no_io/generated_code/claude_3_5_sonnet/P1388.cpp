#include <stdio.h>
#include <string.h>

#define MAX_N 15
#define MAX_K 14

long long dp[MAX_N][MAX_N][MAX_K + 1];
int a[MAX_N];
int n, k;

long long max(long long a, long long b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < n; i++) {
        dp[i][i][0] = a[i];
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len <= n; i++) {
            int j = i + len - 1;
            for (int m = 0; m <= k && m < len - 1; m++) {
                for (int p = i; p < j; p++) {
                    if (m == 0) {
                        dp[i][j][m] = max(dp[i][j][m], dp[i][p][0] + dp[p+1][j][0]);
                    } else {
                        for (int q = 0; q <= m; q++) {
                            dp[i][j][m] = max(dp[i][j][m], dp[i][p][q] * dp[p+1][j][m-q-1]);
                        }
                    }
                }
            }
        }
    }

    printf("%lld\n", dp[0][n-1][k]);

    return 0;
}