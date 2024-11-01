#include <stdio.h>
#include <string.h>

int n, m, c[1024], f[1024][1024], dp[1024][1024], g[1024];

int main() {
    scanf("%d", &n);
    m = 1 << n;
    for (int i = 1; i <= m; i++) scanf("%d", &c[i]);
    for (int i = 1; i <= m; i++) {
        for (int j = i + 1; j <= m; j++) {
            scanf("%d", &f[i][j]);
        }
    }

    // 初始化dp数组
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= i; j++) {
            dp[i][j] = 0;
            for (int k = 0; k <= j; k++) {
                dp[i][j] += f[i][i - j + k] * g[k];
            }
            dp[i][j] += c[i] * (j - (i + 1) / 2);
        }
    }

    // 动态规划求解最小费用
    for (int i = m; i > 1; i >>= 1) {
        for (int j = 1; j <= i; j++) {
            for (int k = 0; k <= j; k++) {
                dp[j][k] = dp[j][k] + dp[i + j][j - k];
            }
        }
        for (int j = 1; j <= (i >> 1); j++) {
            int min = 0x7fffffff;
            for (int k = 0; k <= j; k++) {
                if (dp[j][k] < min) min = dp[j][k];
            }
            dp[j][j] = min;
        }
    }

    printf("%d\n", dp[1][0]);
    return 0;
}