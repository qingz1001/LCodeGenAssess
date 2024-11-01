#include <stdio.h>

long long derangement(int n) {
    if (n == 0) return 1;
    if (n == 1) return 0;
    long long dp[n + 1];
    dp[0] = 1;
    dp[1] = 0;
    for (int i = 2; i <= n; i++) {
        dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]);
    }
    return dp[n];
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%lld\n", derangement(n));
    return 0;
}