#include <stdio.h>
#include <stdlib.h>

#define MAXN 501
#define MAXM 501
#define MAX 1000000

int n, m;
int a[MAXN][MAXM];
int b[MAXN][MAXM];
int s[MAXN][MAXM];
int c[MAXN][MAXM];
int l[MAXN][MAXM];
int r[MAXN][MAXM];
int dp[MAXN][MAXM];

void init() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = MAX;
            b[i][j] = 0;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // 初始化
    init();

    // 第一行处理，蓄水厂只能在第一行
    for (int j = 1; j <= m; j++) {
        if (b[1][j] == 0) {
            b[1][j] = 1;
            dp[1][j] = 0;
            for (int i = 2; i <= n; i++) {
                for (int k = 1; k <= m; k++) {
                    if (dp[i][k] > dp[i-1][j] + a[i][k] - a[i-1][j]) {
                        dp[i][k] = dp[i-1][j] + a[i][k] - a[i-1][j];
                    }
                }
            }
        }
    }

    // 计算每行的最小dp值
    for (int i = 1; i <= n; i++) {
        int min = MAX;
        for (int j = 1; j <= m; j++) {
            if (dp[i][j] < min) {
                min = dp[i][j];
            }
        }
        for (int j = 1; j <= m; j++) {
            if (dp[i][j] == min) {
                s[i][j] = 1;
            }
        }
    }

    // 更新dp值
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == 1) {
                for (int k = 1; k <= m; k++) {
                    if (dp[i+1][k] > dp[i][j] + a[i+1][k] - a[i][j]) {
                        dp[i+1][k] = dp[i][j] + a[i+1][k] - a[i][j];
                    }
                }
            }
        }
    }

    // 计算每行的最小dp值
    for (int i = 1; i <= n; i++) {
        int min = MAX;
        for (int j = 1; j <= m; j++) {
            if (dp[i][j] < min) {
                min = dp[i][j];
            }
        }
        for (int j = 1; j <= m; j++) {
            if (dp[i][j] == min) {
                c[i][j] = 1;
            }
        }
    }

    // 检查最后一行是否都满足条件
    int flag = 1;
    for (int j = 1; j <= m; j++) {
        if (c[n][j] == 0) {
            flag = 0;
            break;
        }
    }

    // 输出结果
    if (flag) {
        printf("1\n");
        int min = MAX;
        for (int j = 1; j <= m; j++) {
            if (dp[1][j] < min) {
                min = dp[1][j];
            }
        }
        printf("%d\n", min);
    } else {
        printf("0\n");
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (i != 1 && !b[i][j] && !c[i][j]) {
                    ans++;
                }
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}