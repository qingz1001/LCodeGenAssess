#include <stdio.h>

long long derangement(int n) {
    if (n == 0) return 1;
    if (n == 1) return 0;
    if (n == 2) return 1;
    
    long long dp[21] = {1, 0, 1};
    for (int i = 3; i <= n; i++) {
        dp[i] = (i - 1) * (dp[i-1] + dp[i-2]);
    }
    
    return dp[n];
}

int main() {
    int n;
    scanf("%d", &n);
    
    long long result = derangement(n);
    printf("%lld\n", result);
    
    return 0;
}