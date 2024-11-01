#include <stdio.h>
#include <string.h>

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    char num[N+1];
    scanf("%s", num);

    // dp[i][j] 表示前 i 个字符分成 j 段的最大乘积
    long long dp[N+1][K+1];
    memset(dp, 0, sizeof(dp));

    // 初始化，单个字符的乘积为该字符本身
    for (int i = 1; i <= N; i++) {
        dp[i][1] = atoi(num + i - 1);
    }

    // 动态规划求解
    for (int j = 2; j <= K; j++) { // 分段数
        for (int i = j; i <= N; i++) { // 字符串长度
            for (int m = j - 1; m < i; m++) { // 分割点
                dp[i][j] = (dp[i][j] > dp[m][j-1] * atoi(num + m) ? dp[i][j] : dp[m][j-1] * atoi(num + m));
            }
        }
    }

    printf("%lld\n", dp[N][K]);
    return 0;
}