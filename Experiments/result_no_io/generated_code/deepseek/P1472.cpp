#include <stdio.h>
#include <string.h>

#define MOD 9901
#define MAXN 200
#define MAXK 100

int dp[MAXN][MAXK];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= k; i++) {
        dp[1][i] = 1;
    }

    for (int d = 1; d <= k; d++) {
        for (int nodes = 3; nodes <= n; nodes += 2) {
            for (int left = 1; left < nodes; left += 2) {
                int right = nodes - 1 - left;
                dp[nodes][d] = (dp[nodes][d] + dp[left][d - 1] * dp[right][d - 1]) % MOD;
            }
        }
    }

    printf("%d\n", (dp[n][k] - dp[n][k - 1] + MOD) % MOD);

    return 0;
}