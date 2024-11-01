#include <stdio.h>
#include <string.h>

int main() {
    char str[1001];
    scanf("%s", str);
    int len = strlen(str);
    int dp[1001][1001] = {0};

    // 计算最长回文子序列长度
    for (int i = len - 1; i >= 0; i--) {
        dp[i][i] = 1;
        for (int j = i + 1; j < len; j++) {
            if (str[i] == str[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = (dp[i + 1][j] > dp[i][j - 1]) ? dp[i + 1][j] : dp[i][j - 1];
            }
        }
    }

    // 输出最少插入字符数
    printf("%d\n", len - dp[0][len - 1]);
    return 0;
}