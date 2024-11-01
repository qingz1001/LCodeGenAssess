#include <stdio.h>
#include <string.h>

#define MAX_N 70
#define INF 0x3f3f3f3f

int n;
int h[MAX_N], t[MAX_N];
int dp[MAX_N][MAX_N][MAX_N];
int sum[MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void solve() {
    memset(dp, 0x3f, sizeof(dp));
    
    for (int i = 0; i < n; i++) {
        dp[i][i][1] = h[i] * sum[n];
        for (int j = i + 1; j < n; j++) {
            dp[i][j][1] = max(h[i], h[j]) * sum[n];
        }
    }
    
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len <= n; i++) {
            int j = i + len - 1;
            for (int k = 2; k <= 3; k++) {
                for (int m = i; m < j; m++) {
                    dp[i][j][k] = min(dp[i][j][k], dp[i][m][k-1] + dp[m+1][j][1] - h[m+1] * sum[n]);
                }
            }
        }
    }
    
    printf("%d\n", dp[0][n-1][3]);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &h[i], &t[i]);
        sum[i+1] = sum[i] + t[i];
    }
    
    solve();
    
    return 0;
}