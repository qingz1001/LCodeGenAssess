#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1001
#define MAX_M 1001

int n, m, p;
int golds[MAX_N][MAX_M];
int cost[MAX_N];
int dp[MAX_M][MAX_M];

int main() {
    // 读取输入
    scanf("%d %d %d", &n, &m, &p);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &golds[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &cost[i]);
    }

    // 初始化dp数组
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = -99999999; // 初始化为一个很小的值，表示不可达
        }
    }

    // 初始状态
    for (int i = 1; i <= n; i++) {
        dp[1][i] = golds[i][1] - cost[i];
    }

    // 动态规划
    for (int t = 2; t <= m; t++) {
        for (int start = 1; start <= n; start++) {
            for (int end = 1; end <= n; end++) {
                int prev = (start == 1) ? n : start - 1;
                int next = (end == n) ? 1 : end + 1;
                if (dp[t-1][prev] != -99999999) {
                    dp[t][end] = dp[t-1][prev] + golds[next][t] - cost[end];
                }
            }
        }
    }

    // 找到最大值
    int max_gold = -99999999;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (j <= p) {
                if (dp[j][i] > max_gold) {
                    max_gold = dp[j][i];
                }
            }
        }
    }

    // 输出结果
    printf("%d\n", max_gold);

    return 0;
}