#include <stdio.h>
#include <string.h>

#define MAXN 205
#define MAXM 205
#define MAXK 205

int n, m, k;
int f[MAXN][MAXM];
char c[MAXN][MAXM];
int dp[MAXK][MAXM];

int main() {
    // 读取输入
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d %c", &f[i][j], &c[i][j]);
        }
    }

    // 动态规划求解最大得分
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            for (int l = 0; l <= m; l++) {
                dp[j][l] = -1; // 初始化为-1，表示不可能的状态
            }
        }
        dp[0][0] = 0; // 初始状态，没有子弹且没有打砖块

        for (int j = 0; j <= k; j++) {
            for (int l = 0; l <= m; l++) {
                if (dp[j][l] != -1) {
                    for (int t = 0; t <= 1; t++) {
                        int new_j = j + t;
                        int new_l = l;
                        if (new_j <= k) {
                            if (c[i][l] == 'Y' && t == 1) {
                                new_l++;
                            }
                            dp[new_j][new_l] = dp[new_j][new_l] > dp[j][l] + f[i][l] ? dp[new_j][new_l] : dp[j][l] + f[i][l];
                        }
                    }
                }
            }
        }
    }

    // 找到最大得分
    int max_score = 0;
    for (int j = 0; j <= k; j++) {
        for (int l = 0; l <= m; l++) {
            max_score = max_score > dp[j][l] ? max_score : dp[j][l];
        }
    }

    // 输出最大得分
    printf("%d\n", max_score);
    return 0;
}