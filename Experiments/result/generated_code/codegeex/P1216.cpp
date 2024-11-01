#include <stdio.h>
#include <string.h>

#define MAX_R 1001

int triangle[MAX_R][MAX_R];
int dp[MAX_R][MAX_R];

int main() {
    int r;
    scanf("%d", &r);

    // 读取输入的数字金字塔
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= i; j++) {
            scanf("%d", &triangle[i][j]);
        }
    }

    // 动态规划计算最大路径和
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= i; j++) {
            if (i == 1) {
                dp[i][j] = triangle[i][j];
            } else if (j == 1) {
                dp[i][j] = triangle[i][j] + dp[i-1][j];
            } else if (j == i) {
                dp[i][j] = triangle[i][j] + dp[i-1][j-1];
            } else {
                dp[i][j] = triangle[i][j] + (dp[i-1][j-1] > dp[i-1][j] ? dp[i-1][j-1] : dp[i-1][j]);
            }
        }
    }

    // 找到最大路径和
    int max = 0;
    for (int j = 1; j <= r; j++) {
        if (dp[r][j] > max) {
            max = dp[r][j];
        }
    }

    // 输出结果
    printf("%d\n", max);

    return 0;
}