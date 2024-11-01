#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_K 10

int n, k, a, b, c;
int grid[MAX_N + 1][MAX_N + 1];
int dp[MAX_N + 1][MAX_N + 1][MAX_K + 1];

int main() {
    // 读取输入
    scanf("%d %d %d %d %d", &n, &k, &a, &b, &c);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    // 初始化dp数组，设置为一个很大的值
    memset(dp, 0x3f, sizeof(dp));
    dp[1][1][k] = 0; // 起点处初始油量为k，费用为0

    // 动态规划求解最小费用
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int l = 0; l <= k; l++) {
                if (dp[i][j][l] == 0x3f3f3f3f) continue; // 如果当前状态不可达，跳过

                // 沿着X轴方向移动
                if (i + 1 <= n) {
                    int nextFuel = l - 1;
                    int nextCost = dp[i][j][l];
                    if (grid[i][j]) {
                        nextCost += a; // 遇到油库，加油
                        nextFuel = k;
                    }
                    dp[i + 1][j][nextFuel] = (nextFuel >= 0) ? 
                        fmin(dp[i + 1][j][nextFuel], nextCost + b) : 
                        fmin(dp[i + 1][j][k], nextCost + b + c);
                }

                // 沿着Y轴方向移动
                if (j + 1 <= n) {
                    int nextFuel = l - 1;
                    int nextCost = dp[i][j][l];
                    if (grid[i][j]) {
                        nextCost += a; // 遇到油库，加油
                        nextFuel = k;
                    }
                    dp[i][j + 1][nextFuel] = (nextFuel >= 0) ? 
                        fmin(dp[i][j + 1][nextFuel], nextCost + b) : 
                        fmin(dp[i][j + 1][k], nextCost + b + c);
                }
            }
        }
    }

    // 找到到达终点的最小费用
    int minCost = 0x3f3f3f3f;
    for (int l = 0; l <= k; l++) {
        minCost = fmin(minCost, dp[n][n][l]);
    }

    // 输出结果
    printf("%d\n", minCost);
    return 0;
}