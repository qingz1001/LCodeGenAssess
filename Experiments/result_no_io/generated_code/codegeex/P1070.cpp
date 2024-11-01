#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001

int n, m, p;
int road[MAXN][MAXN], cost[MAXN];
int dp[MAXN][MAXN];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int i, j, k;
    scanf("%d %d %d", &n, &m, &p);
    
    // 读取每段马路上每个单位时间的金币数量
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            scanf("%d", &road[i][j]);
        }
    }
    
    // 读取每个机器人工厂购买机器人的花费
    for (i = 1; i <= n; i++) {
        scanf("%d", &cost[i]);
    }
    
    // 初始化dp数组
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            dp[i][j] = -1e9;
        }
    }
    dp[0][1] = 0;
    
    // 动态规划计算最大金币数
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            for (k = 1; k <= p; k++) {
                if (i - k >= 0 && dp[i - k][j] != -1e9) {
                    dp[i][j] = max(dp[i][j], dp[i - k][j] + road[j][i] - cost[j]);
                }
            }
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        }
    }
    
    // 找到最大金币数
    int ans = -1e9;
    for (i = 1; i <= n; i++) {
        ans = max(ans, dp[m][i]);
    }
    
    printf("%d\n", ans);
    return 0;
}