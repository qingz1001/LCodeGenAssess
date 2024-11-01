#include <stdio.h>
#include <string.h>

int dp[51][51];

int main() {
    char s[51];
    scanf("%s", s + 1);
    int len = strlen(s + 1);

    // 初始化dp数组
    for (int i = 0; i <= len; i++) {
        for (int j = 0; j <= len; j++) {
            dp[i][j] = 0x3f3f3f3f; // 使用一个大数初始化
        }
    }

    // 初始化单个字符的情况
    for (int i = 1; i <= len; i++) {
        dp[i][i] = 1;
    }

    // 动态规划求解
    for (int l = 2; l <= len; l++) {
        for (int i = 1; i + l - 1 <= len; i++) {
            int j = i + l - 1;
            dp[i][j] = dp[i + 1][j] + 1; // 初始状态，将最后一个字符单独处理

            // 检查从i到j的子串是否可以压缩
            for (int k = i; k < j; k++) {
                if (s[k] == s[j]) {
                    dp[i][j] = dp[i][j] < dp[i][k] + dp[k + 1][j] ? dp[i][j] : dp[i][k] + dp[k + 1][j];
                }
            }

            // 检查是否有重复的模式
            for (int k = i; k < j; k++) {
                if (dp[i][k] + dp[k + 1][j] < dp[i][j]) {
                    dp[i][j] = dp[i][k] + dp[k + 1][j];
                }
            }
        }
    }

    printf("%d\n", dp[1][len]);
    return 0;
}