#include <stdio.h>

#define MAX_V 25
#define MAX_N 10000

long long dp[MAX_N + 1];

int main() {
    int V, N;
    int coins[MAX_V];

    // 读取货币种类数和目标金额
    scanf("%d %d", &V, &N);

    // 读取每种货币的面值
    for (int i = 0; i < V; i++) {
        scanf("%d", &coins[i]);
    }

    // 初始化dp数组，dp[i]表示凑足i元的方法数
    dp[0] = 1; // 凑足0元的方法数是1（即什么都不选）

    // 动态规划计算凑足不同金额的方法数
    for (int i = 0; i < V; i++) {
        for (int j = coins[i]; j <= N; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }

    // 输出结果
    printf("%lld\n", dp[N]);

    return 0;
}