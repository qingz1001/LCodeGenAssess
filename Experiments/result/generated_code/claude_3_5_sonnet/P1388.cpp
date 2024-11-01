#include <stdio.h>
#include <string.h>

#define MAX_N 15
#define MAX_K 14

long long dp[MAX_N][MAX_K + 1];
long long sum[MAX_N][MAX_N];
int a[MAX_N];
int n, k;

long long max(long long a, long long b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // 预处理sum数组
    for (int i = 0; i < n; i++) {
        sum[i][i] = a[i];
        for (int j = i + 1; j < n; j++) {
            sum[i][j] = sum[i][j-1] + a[j];
        }
    }

    // 初始化dp数组
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; i++) {
        dp[i][0] = sum[0][i];
    }

    // 动态规划
    for (int j = 1; j <= k; j++) {
        for (int i = j; i < n; i++) {
            for (int m = j - 1; m < i; m++) {
                dp[i][j] = max(dp[i][j], dp[m][j-1] * sum[m+1][i]);
            }
        }
    }

    printf("%lld\n", dp[n-1][k]);

    return 0;
}