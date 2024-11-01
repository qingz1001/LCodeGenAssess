#include <stdio.h>

// 计算卡特兰数
long long catalan(int n) {
    long long dp[n + 1];
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i] = 0;
        for (int j = 0; j < i; j++) {
            dp[i] += dp[j] * dp[i - 1 - j];
        }
    }
    return dp[n];
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%lld\n", catalan(n));
    return 0;
}