#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 505

int n;
int balls[MAX_N];
int dp[MAX_N][MAX_N];

int min(int a, int b) {
    return a < b ? a : b;
}

void eliminate(int left, int right) {
    while (left > 0 && right <= n && balls[left] == balls[right]) {
        left--;
        right++;
    }
    dp[left+1][right-1] = 0;
}

int solve(int left, int right) {
    if (left > right) return 0;
    if (dp[left][right] != -1) return dp[left][right];
    
    dp[left][right] = 1 + solve(left+1, right);
    
    for (int i = left+1; i <= right; i++) {
        if (balls[left] == balls[i]) {
            int result = solve(left+1, i-1) + solve(i+1, right);
            if (i == left+1 || balls[left] != balls[left+1]) {
                result++;
            }
            dp[left][right] = min(dp[left][right], result);
        }
    }
    
    return dp[left][right];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &balls[i]);
    }
    
    memset(dp, -1, sizeof(dp));
    
    for (int len = 2; len <= n; len++) {
        for (int left = 1; left <= n-len+1; left++) {
            int right = left + len - 1;
            if (balls[left] == balls[right] && (len == 2 || dp[left+1][right-1] == 0)) {
                eliminate(left, right);
            }
        }
    }
    
    printf("%d\n", solve(1, n));
    
    return 0;
}