#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    unsigned long long dp[1001] = {0};
    dp[1] = 1;
    dp[2] = 2;
    
    for (int i = 3; i <= n; i++) {
        dp[i] = (dp[i - 1] + dp[i - 2]) % 100000000;
    }
    
    printf("%llu\n", dp[n]);
    
    return 0;
}