#include <stdio.h>
#include <string.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

int dp[25][10005][6]; // dp[i][j][k] 表示高度为 i，位置为 j，连跳次数为 k 时的最大收益
int a[25][10005]; // 地图收益
int n, m, cost1, cost2; // n: 地图长度, m: 地图高度, cost1: 升级跳跃高度花费, cost2: 升级连跳数花费

int main() {
    scanf("%d%d%d%d", &n, &m, &cost1, &cost2);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int maxJumpHeight = m; // 跳跃高度上限
    int maxLeapCount = 5; // 最大连跳次数

    for (int k = 1; k <= maxLeapCount; k++) {
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j][k] = -1; // 初始化为 -1 表示不可达
            }
        }
        dp[1][1][k] = 0; // 起点初始化

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (a[i][j] == -1) continue; // 不可通过点跳过

                // 普通跳跃
                for (int x = i + 1; x <= i + maxJumpHeight && x <= m; x++) {
                    if (a[x][j] != -1) {
                        dp[x][j][k] = max(dp[x][j][k], dp[i][j][k] + a[x][j]);
                    }
                }

                // 连跳
                for (int x = i + 1; x <= i + maxJumpHeight && x <= m; x++) {
                    for (int l = 1; l < k; l++) {
                        if (dp[i][j][l] != -1) {
                            dp[x][j][k] = max(dp[x][j][k], dp[i][j][l] + a[x][j]);
                        }
                    }
                }
            }
        }
    }

    int maxScore = -1;
    int minLeapCount = maxLeapCount;
    int minJumpHeight = maxJumpHeight;

    for (int k = 1; k <= maxLeapCount; k++) {
        for (int i = 1; i <= m; i++) {
            if (dp[i][n][k] > maxScore) {
                maxScore = dp[i][n][k];
                minLeapCount = k;
                minJumpHeight = i;
            }
        }
    }

    if (maxScore == -1) {
        printf("mission failed\n");
    } else {
        printf("%d %d %d\n", maxScore, minLeapCount, minJumpHeight);
    }

    return 0;
}