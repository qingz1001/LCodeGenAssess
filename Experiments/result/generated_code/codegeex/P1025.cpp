#include <stdio.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int dp[201][7]; // dp[i][j] 表示将整数 i 分成 j 份的不同分法数

    // 初始化
    for (int i = 1; i <= n; i++) {
        dp[i][1] = 1; // 将 i 分成 1 份只有一种方法，即 i 本身
    }

    // 动态规划填表
    for (int i = 2; i <= k; i++) { // 先枚举分成 i 份
        for (int j = i; j <= n; j++) { // 再枚举整数 j
            for (int x = 1; x < j; x++) { // 最后枚举第一个数的值 x
                dp[j][i] += dp[j - x][i - 1]; // 将 j - x 分成 i - 1 份的方法数
            }
        }
    }

    // 输出结果
    printf("%d\n", dp[n][k]);

    return 0;
}