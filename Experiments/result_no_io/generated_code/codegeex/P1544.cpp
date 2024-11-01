#include <stdio.h>
#include <limits.h>

#define MAX_N 100
#define MAX_K (MAX_N * (MAX_N + 1) / 2)

int n, k;
int pyramid[MAX_N][MAX_N];
int dp[MAX_N][MAX_N][MAX_K + 1];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    // 读取输入
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%d", &pyramid[i][j]);
        }
    }

    // 初始化dp数组，所有值设为负无穷大
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int l = 0; l <= k; l++) {
                dp[i][j][l] = INT_MIN;
            }
        }
    }

    // 初始状态
    dp[0][0][0] = pyramid[0][0];

    // 动态规划求解
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            for (int l = 0; l <= k; l++) {
                if (j > 0) {
                    dp[i][j][l] = max(dp[i][j][l], dp[i-1][j-1][l] + pyramid[i][j]);
                }
                if (l > 0) {
                    dp[i][j][l] = max(dp[i][j][l], dp[i-1][j][l-1] + pyramid[i][j] * 3);
                }
            }
        }
    }

    // 找到最大得分
    int result = INT_MIN;
    for (int j = 0; j < n; j++) {
        result = max(result, dp[n-1][j][k]);
    }

    // 输出结果
    printf("%d\n", result);

    return 0;
}