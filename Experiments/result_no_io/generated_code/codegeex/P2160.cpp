#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 70
#define MAX_H 300
#define MAX_T 30

int n;
int h[MAX_N], t[MAX_N];
int dp[MAX_H + 1][MAX_T + 1];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int i, j, k;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d%d", &h[i], &t[i]);
    }

    // 初始化dp数组
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    // 动态规划求解
    for (i = 0; i < n; i++) {
        for (j = MAX_H; j >= h[i]; j--) {
            for (k = MAX_T; k >= t[i]; k--) {
                dp[j][k] = max(dp[j][k], max(dp[j - h[i]][k - t[i]] + h[i], dp[j - h[i]][k]));
            }
        }
    }

    // 找到最大高度
    int max_height = 0;
    for (i = 0; i <= MAX_H; i++) {
        max_height = max(max_height, dp[i][MAX_T]);
    }

    // 计算最小面积
    int min_area = max_height * (dp[MAX_H][MAX_T] + dp[MAX_H][MAX_T - 1] + dp[MAX_H][MAX_T - 2]);

    printf("%d\n", min_area);
    return 0;
}