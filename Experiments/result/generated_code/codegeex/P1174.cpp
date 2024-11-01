#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    int f[201][201] = {0}; // 存储每列砖块的得分
    char c[201][201]; // 存储每列砖块是否有奖励子弹
    int dp[201][201] = {0}; // 动态规划数组
    
    // 读取输入
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d %c", &f[i][j], &c[i][j]);
        }
    }
    
    // 动态规划求解
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            for (int l = 1; l <= k; l++) {
                if (l > i) break; // 子弹数量不足以打碎当前行的砖块
                dp[i][l] = max(dp[i][l], dp[i-1][l-i] + f[i][j]); // 不打当前列的砖块
                if (c[i][j] == 'Y' && l < k) {
                    dp[i][l+1] = max(dp[i][l+1], dp[i-1][l-i] + f[i][j]); // 打当前列的砖块并获得奖励子弹
                }
            }
        }
    }
    
    // 找到最大得分
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[i][k]);
    }
    
    printf("%d\n", ans);
    return 0;
}