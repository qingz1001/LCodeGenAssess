#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 205

int n;
int S[N], T[N];
int f[N][N], g[N][N], p[N][N];
int ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &S[i], &T[i]);
    }

    // 计算每个活动结束的时间
    for (int i = 1; i <= n; i++) {
        p[i][i] = S[i] + T[i];
    }
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            p[i][j] = p[i][j - 1] + T[j];
        }
    }

    // 初始化 f 和 g 数组
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            f[i][j] = g[i][j] = -1;
        }
    }

    // 初始化单个活动的 f 和 g 值
    for (int i = 1; i <= n; i++) {
        f[i][0] = g[i][0] = 1;
    }

    // 动态规划计算 f 和 g 数组
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (f[i - 1][j] > g[i - 1][j]) {
                f[i][j] = f[i - 1][j] + 1;
                g[i][j] = g[i - 1][j];
            } else {
                f[i][j] = f[i - 1][j];
                g[i][j] = g[i - 1][j] + 1;
            }
            if (p[i][j] <= S[i + 1]) {
                f[i + 1][j] = f[i][j];
                g[i + 1][j] = g[i][j];
            } else {
                f[i + 1][j] = f[i][j - 1];
                g[i + 1][j] = g[i][j - 1] + 1;
            }
        }
    }

    // 计算答案
    ans = f[n][n];
    printf("%d\n", ans);

    // 计算每个活动必须选择时的答案
    for (int i = 1; i <= n; i++) {
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        f[i][0] = g[i][0] = 1;
        for (int j = i + 1; j <= n; j++) {
            if (p[i][j - 1] <= S[j]) {
                f[j][0] = f[i][0] + 1;
                g[j][0] = g[i][0];
            } else {
                f[j][0] = f[i][0];
                g[j][0] = g[i][0] + 1;
            }
        }
        for (int j = 1; j <= n; j++) {
            if (f[j - 1][j] > g[j - 1][j]) {
                f[j][j] = f[j - 1][j] + 1;
                g[j][j] = g[j - 1][j];
            } else {
                f[j][j] = f[j - 1][j];
                g[j][j] = g[j - 1][j] + 1;
            }
            if (p[i][j] <= S[i + 1]) {
                f[i + 1][j] = f[i][j];
                g[i + 1][j] = g[i][j];
            } else {
                f[i + 1][j] = f[i][j - 1];
                g[i + 1][j] = g[i][j - 1] + 1;
            }
        }
        int temp = f[n][n];
        if (temp < ans) temp = ans;
        printf("%d\n", temp);
    }

    return 0;
}