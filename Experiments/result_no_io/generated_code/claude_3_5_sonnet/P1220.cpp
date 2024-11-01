#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 51
#define INF 1e9

int n, c;
int pos[MAX_N], power[MAX_N];
long long dp[MAX_N][MAX_N];

long long min(long long a, long long b) {
    return a < b ? a : b;
}

long long solve() {
    memset(dp, 0x3f, sizeof(dp));
    dp[c][c] = 0;

    for (int len = 2; len <= n; len++) {
        for (int l = 1; l <= n - len + 1; l++) {
            int r = l + len - 1;
            long long sum = 0;
            for (int k = l; k <= r; k++) {
                sum += power[k];
            }

            if (l <= c && c <= r) {
                dp[l][r] = sum * (pos[r] - pos[l]);
            } else {
                dp[l][r] = min(dp[l+1][r] + sum * (pos[l+1] - pos[l]),
                               dp[l][r-1] + sum * (pos[r] - pos[r-1]));
            }
        }
    }

    return dp[1][n];
}

int main() {
    scanf("%d %d", &n, &c);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &pos[i], &power[i]);
    }

    printf("%lld\n", solve());
    return 0;
}