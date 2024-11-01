#include <stdio.h>
#include <string.h>

int main() {
    char s[1001];
    scanf("%s", s);
    int len = strlen(s);
    int dp[1001][1001] = {0};

    // 初始化 dp 数组，当两个字符串长度差 1 时，需要插入一个字符
    for (int i = 1; i < len; i++) {
        dp[i][i + 1] = s[i] == s[i - 1] ? 0 : 1;
    }

    // 填充 dp 数组
    for (int l = 3; l <= len; l++) {
        for (int i = 0; i + l - 1 < len; i++) {
            int j = i + l - 1;
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1];
            } else {
                dp[i][j] = 1 + dp[i + 1][j - 1];
            }
        }
    }

    // 输出结果
    printf("%d\n", dp[0][len - 1]);

    return 0;
}