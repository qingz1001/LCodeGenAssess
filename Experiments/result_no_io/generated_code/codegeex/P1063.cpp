#include <stdio.h>

#define MAXN 102

int a[MAXN], dp[MAXN][MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        a[i + n] = a[i]; // 复制一遍数组，实现环状处理
    }

    for (int len = 3; len <= n + 1; len++) { // 枚举区间长度
        for (int i = 1; i <= n; i++) { // 枚举区间起点
            int j = i + len - 1; // 区间终点
            for (int k = i; k < j; k++) { // 枚举分割点
                dp[i][j] = (dp[i][j] > dp[i][k] + dp[k + 1][j] + a[i] * a[k + 1] * a[j + 1]) ? dp[i][j] : dp[i][k] + dp[k + 1][j] + a[i] * a[k + 1] * a[j + 1];
            }
        }
    }

    int max_energy = 0;
    for (int i = 1; i <= n; i++) {
        max_energy = (max_energy > dp[i][i + n - 1]) ? max_energy : dp[i][i + n - 1];
    }

    printf("%d\n", max_energy);
    return 0;
}