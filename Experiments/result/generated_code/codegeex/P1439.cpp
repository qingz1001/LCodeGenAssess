#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    int P1[n], P2[n], pos[n + 1];
    
    // 读取P1并记录每个数的位置
    for (int i = 0; i < n; i++) {
        scanf("%d", &P1[i]);
        pos[P1[i]] = i;
    }
    
    // 读取P2
    for (int i = 0; i < n; i++) {
        scanf("%d", &P2[i]);
    }
    
    int dp[n + 1];
    memset(dp, 0, sizeof(dp));
    
    // 动态规划求解最长公共子序列
    for (int i = 0; i < n; i++) {
        dp[i + 1] = dp[i];
        if (pos[P2[i]] != -1) {
            dp[i + 1] = (dp[i + 1] > dp[pos[P2[i]] + 1] + 1) ? dp[i + 1] : dp[pos[P2[i]] + 1] + 1;
        }
    }
    
    // 输出最长公共子序列的长度
    printf("%d\n", dp[n]);
    
    return 0;
}