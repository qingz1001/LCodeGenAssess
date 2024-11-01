#include <stdio.h>
#include <limits.h>

#define MAX_N 500000

int n, k, L, R;
int a[MAX_N + 1];
int sum[MAX_N + 1];
int dp[MAX_N + 1];

int main() {
    // 读取输入
    scanf("%d%d%d%d", &n, &k, &L, &R);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum[i] = sum[i - 1] + a[i];
    }

    // 动态规划求解
    for (int i = 1; i <= n; i++) {
        dp[i] = INT_MIN;
        for (int j = i - L; j >= i - R; j--) {
            if (j < 0) break;
            dp[i] = (dp[i] > dp[j] + sum[i] - sum[j]) ? dp[i] : dp[j] + sum[i] - sum[j];
        }
    }

    // 找出最大的k个dp值
    int max_k = k;
    for (int i = 1; i <= n; i++) {
        if (max_k > 0) {
            max_k--;
        } else {
            dp[i] = (dp[i] > dp[i - 1]) ? dp[i] : dp[i - 1];
        }
    }

    // 输出结果
    printf("%d\n", dp[n]);
    return 0;
}