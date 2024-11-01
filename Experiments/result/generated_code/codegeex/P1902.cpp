#include <stdio.h>
#include <limits.h>

#define MAXN 1001

int p[MAXN][MAXN];
int dp[MAXN][MAXN];
int n, m;

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &p[i][j]);
        }
    }

    // 初始化dp数组，设置为一个较大的值
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = INT_MAX;
        }
    }

    // 初始化第一行的dp值
    for (int j = 1; j <= m; j++) {
        dp[1][j] = 0;
    }

    // 动态规划计算最小伤害值
    for (int i = 2; i <= n - 1; i++) {
        for (int j = 1; j <= m; j++) {
            int left = dp[i - 1][j - 1];
            int up = dp[i - 1][j];
            int right = dp[i - 1][j + 1];
            dp[i][j] = min(left, min(up, right)) + p[i][j];
        }
    }

    // 找到最后一行的最小值
    int ans = INT_MAX;
    for (int j = 1; j <= m; j++) {
        ans = min(ans, dp[n - 1][j]);
    }

    printf("%d\n", ans);
    return 0;
}