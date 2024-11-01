#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAXN 500000
#define MAXG 2000

int n, d, k;
int x[MAXN + 1], s[MAXN + 1];
int dp[MAXG + 1][MAXN + 1];
int jump[MAXG + 1][MAXN + 1];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d%d%d", &n, &d, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &x[i], &s[i]);
    }

    // 初始化dp数组
    for (int i = 0; i <= MAXG; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = INT_MIN;
        }
    }
    dp[0][0] = 0;

    // 动态规划求解
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= MAXG; j++) {
            int minDist = INT_MAX, maxDist = INT_MIN;
            if (j < d) {
                minDist = max(1, d - j);
                maxDist = min(d + j, x[i]);
            } else {
                minDist = 1;
                maxDist = d + j;
            }
            for (int prev = i - 1; prev >= 0; prev--) {
                if (x[i] - x[prev] >= minDist && x[i] - x[prev] <= maxDist) {
                    dp[j][i] = max(dp[j][i], dp[j][prev] + s[i]);
                }
            }
        }
    }

    // 找到最小的金币数
    int minCoins = INT_MAX;
    for (int j = 0; j <= MAXG; j++) {
        if (dp[j][n] >= k) {
            minCoins = min(minCoins, j);
        }
    }

    // 输出结果
    if (minCoins == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", minCoins);
    }

    return 0;
}