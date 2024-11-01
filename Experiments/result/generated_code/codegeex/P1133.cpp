#include <stdio.h>
#include <limits.h>

#define MAX_N 100005
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int n;
int a[MAX_N][3];
int dp[MAX_N][3];

int main() {
    // 读取输入
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &a[i][0], &a[i][1], &a[i][2]);
    }

    // 动态规划求解
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            // 初始状态
            dp[i][0] = a[i][0];
            dp[i][1] = a[i][1];
            dp[i][2] = a[i][2];
        } else {
            // 状态转移
            dp[i][0] = MAX(dp[i-1][1], dp[i-1][2]) + a[i][0];
            dp[i][1] = MAX(dp[i-1][0], dp[i-1][2]) + a[i][1];
            dp[i][2] = MAX(dp[i-1][0], dp[i-1][1]) + a[i][2];
        }
    }

    // 处理环形结构
    int result = 0;
    for (int i = 0; i < n; i++) {
        result = MAX(result, MAX(dp[i][0], MAX(dp[i][1], dp[i][2])));
    }

    // 输出结果
    printf("%d\n", result);

    return 0;
}