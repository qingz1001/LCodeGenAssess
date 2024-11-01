#include <stdio.h>
#include <stdlib.h>

#define MAXN 5005

int N;
int prices[MAXN];
int dp[MAXN];
int count[MAXN];

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &prices[i]);
    }

    // 初始化dp和count数组
    for (int i = 1; i <= N; i++) {
        dp[i] = 1;
        count[i] = 1;
    }

    // 动态规划求解最大购买次数
    for (int i = 2; i <= N; i++) {
        for (int j = 1; j < i; j++) {
            if (prices[j] > prices[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    count[i] = count[j];
                } else if (dp[j] + 1 == dp[i]) {
                    count[i] += count[j];
                }
            }
        }
    }

    // 找到最大购买次数和方案数
    int maxTimes = 0;
    int maxCount = 0;
    for (int i = 1; i <= N; i++) {
        if (dp[i] > maxTimes) {
            maxTimes = dp[i];
            maxCount = count[i];
        } else if (dp[i] == maxTimes) {
            maxCount += count[i];
        }
    }

    printf("%d %d\n", maxTimes, maxCount);
    return 0;
}