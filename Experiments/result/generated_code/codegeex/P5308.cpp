#include <stdio.h>
#include <stdlib.h>

typedef long double ld;

ld dp[100001][11];

ld max(ld a, ld b) {
    return a > b ? a : b;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    // 初始化dp数组，dp[i][j]表示在前i轮淘汰j个人的最大奖金
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = -1;
        }
    }
    dp[0][0] = 0;

    // 动态规划求解
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            for (int l = 0; l <= i; l++) {
                if (dp[i - l][j - 1] != -1) {
                    dp[i][j] = max(dp[i][j], dp[i - l][j - 1] + (ld)l / i);
                }
            }
        }
    }

    // 输出结果
    printf("%.9Lf\n", dp[n][k]);
    return 0;
}