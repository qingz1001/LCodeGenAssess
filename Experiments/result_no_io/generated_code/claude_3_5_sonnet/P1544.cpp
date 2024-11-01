#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_K 5050
#define MAX(a, b) ((a) > (b) ? (a) : (b))

long long dp[MAX_N][MAX_N][MAX_K];
int a[MAX_N][MAX_N];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    memset(dp, -1, sizeof(dp));
    dp[0][0][0] = a[0][0];
    if (k > 0) dp[0][0][1] = 3 * a[0][0];

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            for (int m = 0; m <= k; m++) {
                if (j > 0 && dp[i-1][j-1][m] != -1) {
                    dp[i][j][m] = MAX(dp[i][j][m], dp[i-1][j-1][m] + a[i][j]);
                }
                if (j < i && dp[i-1][j][m] != -1) {
                    dp[i][j][m] = MAX(dp[i][j][m], dp[i-1][j][m] + a[i][j]);
                }
                if (m > 0) {
                    if (j > 0 && dp[i-1][j-1][m-1] != -1) {
                        dp[i][j][m] = MAX(dp[i][j][m], dp[i-1][j-1][m-1] + 3LL * a[i][j]);
                    }
                    if (j < i && dp[i-1][j][m-1] != -1) {
                        dp[i][j][m] = MAX(dp[i][j][m], dp[i-1][j][m-1] + 3LL * a[i][j]);
                    }
                }
            }
        }
    }

    long long ans = -1;
    for (int j = 0; j < n; j++) {
        for (int m = 0; m <= k; m++) {
            ans = MAX(ans, dp[n-1][j][m]);
        }
    }

    printf("%lld\n", ans);

    return 0;
}