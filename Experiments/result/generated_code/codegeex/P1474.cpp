#include <stdio.h>

int main() {
    int v, n;
    scanf("%d%d", &v, &n);
    int coins[v];
    for (int i = 0; i < v; i++) {
        scanf("%d", &coins[i]);
    }

    // 动态规划数组，dp[i] 表示凑成 i 元的方法数
    long long dp[n + 1];
    dp[0] = 1; // 凑成 0 元的方法数为 1

    for (int i = 0; i < v; i++) {
        for (int j = coins[i]; j <= n; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }

    printf("%lld\n", dp[n]);
    return 0;
}