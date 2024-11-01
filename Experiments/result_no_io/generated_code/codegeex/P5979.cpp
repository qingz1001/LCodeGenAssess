#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000005
#define MOD 1000000007

int n;
int c[MAXN], d[MAXN];
int dp[MAXN], pre[MAXN], suf[MAXN];
int st[MAXN], top;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &c[i], &d[i]);
    }

    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        int l = c[i], r = d[i];
        int j = i - 1;

        // Calculate the suffix sum
        suf[i] = dp[i - 1];
        while (j >= 1 && r >= c[j]) {
            suf[i] = (suf[i] + dp[j - 1]) % MOD;
            j -= (r - c[j] + 1);
        }

        // Calculate the prefix sum
        j = i - 1;
        pre[i] = dp[j];
        while (j >= 1 && l <= d[j]) {
            pre[i] = (pre[i] + dp[j - 1]) % MOD;
            j -= (d[j] - l + 1);
        }

        // Calculate the DP value
        dp[i] = pre[i];
        if (j >= 0) {
            dp[i] = (dp[i] - suf[j + 1] + MOD) % MOD;
        }
    }

    int max_groups = 0, ways = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[i] > max_groups) {
            max_groups = dp[i];
            ways = dp[i];
        } else if (dp[i] == max_groups) {
            ways = (ways + dp[i]) % MOD;
        }
    }

    if (max_groups == 0) {
        printf("NIE\n");
    } else {
        printf("%d %d\n", max_groups, ways);
    }

    return 0;
}