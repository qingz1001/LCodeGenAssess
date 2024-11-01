#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 2000001

long long dp[MAX_N][2];
int w[MAX_N];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i <= n; i++) {
        scanf("%d", &w[i]);
    }

    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                long long cost = dp[i][k-i&1] + dp[k+1][(j-k-1)&1] + 1LL * w[i-1] * w[k] * w[j];
                if (cost < dp[i][len&1]) {
                    dp[i][len&1] = cost;
                }
            }
        }
    }

    printf("%lld\n", dp[1][n&1]);
    return 0;
}