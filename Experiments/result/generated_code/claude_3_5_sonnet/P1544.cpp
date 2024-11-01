#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_K 5050
#define MAX(a, b) ((a) > (b) ? (a) : (b))

long long dp[MAX_N+1][MAX_N+1][MAX_K+1];
int a[MAX_N+1][MAX_N+1];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    memset(dp, -0x3f, sizeof(dp));
    dp[1][1][0] = a[1][1];
    dp[1][1][1] = 3 * a[1][1];

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            for (int used = 0; used <= k; used++) {
                if (j > 1) {
                    dp[i][j][used] = MAX(dp[i][j][used], dp[i-1][j-1][used] + a[i][j]);
                    if (used > 0) {
                        dp[i][j][used] = MAX(dp[i][j][used], dp[i-1][j-1][used-1] + 3 * a[i][j]);
                    }
                }
                dp[i][j][used] = MAX(dp[i][j][used], dp[i-1][j][used] + a[i][j]);
                if (used > 0) {
                    dp[i][j][used] = MAX(dp[i][j][used], dp[i-1][j][used-1] + 3 * a[i][j]);
                }
            }
        }
    }

    long long ans = -0x3f3f3f3f3f3f3f3fLL;
    for (int j = 1; j <= n; j++) {
        for (int used = 0; used <= k; used++) {
            ans = MAX(ans, dp[n][j][used]);
        }
    }

    printf("%lld\n", ans);

    return 0;
}