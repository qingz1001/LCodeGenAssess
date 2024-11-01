#include <stdio.h>
#include <string.h>

#define MAX_N 505
#define INF 0x3f3f3f3f

int n, a[MAX_N], dp[MAX_N][MAX_N];

int min(int a, int b) {
    return a < b ? a : b;
}

int solve(int left, int right) {
    if (left > right) return 0;
    if (dp[left][right] != -1) return dp[left][right];
    
    dp[left][right] = 1 + solve(left + 1, right);
    
    for (int i = left + 1; i <= right; i++) {
        if (a[left] == a[i]) {
            int need = solve(left + 1, i - 1);
            if (i == left + 1 || need == 0) {
                dp[left][right] = min(dp[left][right], solve(i + 1, right));
            } else {
                dp[left][right] = min(dp[left][right], need + solve(i + 1, right));
            }
        }
    }
    
    return dp[left][right];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    memset(dp, -1, sizeof(dp));
    printf("%d\n", solve(1, n));
    
    return 0;
}