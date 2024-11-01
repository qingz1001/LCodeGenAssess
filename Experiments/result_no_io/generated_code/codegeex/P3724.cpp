#include <stdio.h>
#include <string.h>

#define MAXN 110
#define MAXM 30
#define INF 0x3f3f3f3f

int n, m, mc;
int a[MAXN], w[MAXN];
int C[MAXM];
int dp[MAXN][MAXN][MAXN][2][3];

int main() {
    // 读取输入
    scanf("%d%d%d", &n, &m, &mc);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &C[i]);
    }

    // 初始化dp数组
    memset(dp, -1, sizeof(dp));
    dp[0][mc][0][0][0] = 0;

    // 动态规划求解
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= mc; j++) {
            for (int k = 0; k <= n; k++) {
                for (int l = 0; l < 2; l++) {
                    for (int t = 0; t < 3; t++) {
                        if (dp[i][j][k][l][t] == -1) continue;

                        // 还一句嘴
                        if (C[l] > 0) {
                            dp[i + 1][j][k][l][t] = dp[i][j][k][l][t];
                        }

                        // 做一天的水题
                        int new_j = j + w[i + 1];
                        if (new_j > mc) new_j = mc;
                        dp[i + 1][new_j][k][l][t] = dp[i][j][k][l][t];

                        // 让自己的等级值L加1
                        dp[i + 1][j][k + 1][l][t] = dp[i][j][k][l][t];

                        // 让自己的讽刺能力F乘以自己当前等级L
                        if (k > 0) {
                            int new_f = 1;
                            for (int x = 1; x <= k; x++) {
                                new_f *= x;
                            }
                            dp[i + 1][j][0][l][t] = dp[i][j][k][l][t];
                        }

                        // 怼大佬
                        if (t < 2 && C[l] >= k) {
                            dp[i + 1][j][0][l + 1][t + 1] = dp[i][j][k][l][t];
                        }
                    }
                }
            }
        }
    }

    // 输出结果
    for (int i = 0; i < m; i++) {
        if (dp[n][mc][0][i][2] != -1) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }

    return 0;
}