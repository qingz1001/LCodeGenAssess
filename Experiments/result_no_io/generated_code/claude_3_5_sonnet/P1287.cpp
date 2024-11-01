#include <stdio.h>

#define MAX_N 11

long long dp[MAX_N][MAX_N];

long long stirling2(int n, int k) {
    if (n == k || k == 1) return 1;
    if (k == 0 || k > n) return 0;
    if (dp[n][k] != 0) return dp[n][k];
    
    dp[n][k] = stirling2(n - 1, k - 1) + k * stirling2(n - 1, k);
    return dp[n][k];
}

int main() {
    int n, r;
    scanf("%d %d", &n, &r);
    
    if (r > n || r == 0) {
        printf("0\n");
    } else {
        long long result = stirling2(n, r);
        printf("%lld\n", result);
    }
    
    return 0;
}