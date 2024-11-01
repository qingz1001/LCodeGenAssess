#include <stdio.h>
#include <string.h>

#define MAXN 160
#define MAXM 505

int n, m;
int a[MAXN][MAXM];
int f[MAXN][MAXM][MAXM];

int main() {
    // 读取输入
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // 预处理 f 数组
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = j; k <= m; k++) {
                f[i][j][k] = f[i][j][k-1] + a[i][k];
            }
        }
    }

    int ans = -0x3f3f3f3f;

    // 枚举 N 的位置
    for (int i = 1; i <= n; i++) {
        for (int j = 3; j <= m; j++) {
            for (int k = 1; k < j; k++) {
                int sum1 = 0, sum2 = 0;
                for (int l = 1; l <= k; l++) {
                    sum1 += f[i][l][j];
                }
                for (int l = k + 1; l <= j; l++) {
                    sum2 += f[i][k][l];
                }
                ans = ans > sum1 + sum2 ? ans : sum1 + sum2;
            }
        }
    }

    // 枚举 O 的位置
    for (int i = 1; i <= n; i++) {
        for (int j = 3; j <= m; j++) {
            for (int k = j + 3; k <= m; k++) {
                int sum1 = 0, sum2 = 0;
                for (int l = j; l <= k; l++) {
                    sum1 += f[i][l][j];
                }
                for (int l = j + 1; l <= k - 1; l++) {
                    sum2 += f[i][l][k];
                }
                ans = ans > sum1 - sum2 ? ans : sum1 - sum2;
            }
        }
    }

    // 枚举 I 的位置
    for (int i = 1; i <= n; i++) {
        for (int j = 3; j <= m; j++) {
            for (int k = j + 3; k <= m; k++) {
                int sum1 = 0, sum2 = 0, sum3 = 0;
                for (int l = j; l <= k; l++) {
                    sum1 += f[i][l][j];
                }
                for (int l = j + 1; l <= k - 1; l++) {
                    sum2 += f[i][l][k];
                }
                for (int l = j; l <= k; l++) {
                    sum3 += f[i][l][k];
                }
                ans = ans > sum1 - sum2 + sum3 ? ans : sum1 - sum2 + sum3;
            }
        }
    }

    // 输出结果
    printf("%d\n", ans);
    return 0;
}