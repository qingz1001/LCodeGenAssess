#include <stdio.h>
#include <string.h>
#include <limits.h>

int main() {
    int L, S, T, M;
    scanf("%d%d%d%d", &L, &S, &T, &M);

    int stones[M];
    for (int i = 0; i < M; i++) {
        scanf("%d", &stones[i]);
    }

    // 如果L小于最大跳跃距离，青蛙无法到达终点
    if (L < T) {
        printf("0\n");
        return 0;
    }

    // 初始化动态规划数组
    int dp[L + 1];
    memset(dp, 0, sizeof(dp));

    // 初始化第一个点
    dp[0] = 0;

    // 计算每个点的最少踩石子数
    for (int i = 1; i <= L; i++) {
        dp[i] = INT_MAX;
        for (int j = S; j <= T && i - j >= 0; j++) {
            dp[i] = dp[i] < dp[i - j] ? dp[i] : dp[i - j];
        }
        for (int k = 0; k < M; k++) {
            if (stones[k] <= i) {
                dp[i]++;
            }
        }
    }

    printf("%d\n", dp[L]);
    return 0;
}