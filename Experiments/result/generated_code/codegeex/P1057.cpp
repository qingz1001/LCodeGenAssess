#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // 初始化dp数组，dp[i][j]表示第i次传球后球在第j个同学手中的方法数
    int dp[31][31] = {0};
    dp[0][0] = 1; // 初始状态，球在小蛮（0号同学）手中

    // 动态规划求解
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (dp[i][j] > 0) {
                dp[i + 1][(j + 1) % n] += dp[i][j]; // 球传给右边的同学
                dp[i + 1][(j - 1 + n) % n] += dp[i][j]; // 球传给左边的同学
            }
        }
    }

    // 输出结果，第m次传球后球在小蛮（0号同学）手中的方法数
    printf("%d\n", dp[m][0]);

    return 0;
}