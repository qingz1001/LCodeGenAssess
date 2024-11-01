#include <stdio.h>
#include <string.h>

int n, m;
int a[360];
int b[130];
int dp[130][360];

int main() {
    // 输入棋盘格子数和爬行卡片数
    scanf("%d%d", &n, &m);
    
    // 输入棋盘每个格子的分数
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    // 输入爬行卡片上的数字
    for (int i = 1; i <= m; i++) {
        scanf("%d", &b[i]);
    }
    
    // 初始化dp数组，设置为一个极小值
    memset(dp, -0x3f, sizeof(dp));
    
    // 起点自动获得第1格的分数
    dp[0][1] = a[1];
    
    // 动态规划计算最大得分
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= 4; k++) {
                if (j - k >= 1) {
                    dp[i][j] = dp[i - 1][j - k] + a[j];
                }
            }
        }
    }
    
    // 找到最大得分
    int maxScore = -0x3f;
    for (int i = 1; i <= n; i++) {
        if (dp[m][i] > maxScore) {
            maxScore = dp[m][i];
        }
    }
    
    // 输出最大得分
    printf("%d\n", maxScore);
    
    return 0;
}