#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_M 200
#define MAX_T 200

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, M, T;
    int m[MAX_N], t[MAX_N];
    int dp[MAX_M + 1][MAX_T + 1];

    // 初始化dp数组
    for (int i = 0; i <= MAX_M; i++) {
        for (int j = 0; j <= MAX_T; j++) {
            dp[i][j] = 0;
        }
    }

    // 读取输入
    scanf("%d %d %d", &n, &M, &T);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &m[i], &t[i]);
    }

    // 动态规划求解
    for (int i = 0; i < n; i++) {
        for (int j = M; j >= m[i]; j--) {
            for (int k = T; k >= t[i]; k--) {
                dp[j][k] = max(dp[j][k], dp[j - m[i]][k - t[i]] + 1);
            }
        }
    }

    // 输出结果
    printf("%d\n", dp[M][T]);

    return 0;
}