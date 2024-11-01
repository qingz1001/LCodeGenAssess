#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX_M 1000
#define INF 0x3f3f3f3f

int n, m;
int p[MAX_N][MAX_M];
int dp[MAX_N][MAX_M];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void solve() {
    memset(dp, 0x3f, sizeof(dp));
    
    // 初始化第一行
    for (int j = 0; j < m; j++) {
        dp[0][j] = 0;
    }
    
    // 动态规划
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int minDamage = INF;
            
            // 从上方来
            minDamage = min(minDamage, max(dp[i-1][j], p[i][j]));
            
            // 从左方来
            if (j > 0) {
                minDamage = min(minDamage, max(dp[i][j-1], p[i][j]));
            }
            
            // 从右方来
            if (j < m - 1) {
                minDamage = min(minDamage, max(dp[i][j+1], p[i][j]));
            }
            
            dp[i][j] = minDamage;
        }
    }
    
    // 找出最后一行的最大值
    int result = 0;
    for (int j = 0; j < m; j++) {
        result = max(result, dp[n-1][j]);
    }
    
    printf("%d\n", result);
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &p[i][j]);
        }
    }
    
    solve();
    
    return 0;
}