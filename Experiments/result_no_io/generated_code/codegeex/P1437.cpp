#include <stdio.h>

#define MAXN 51
#define MAXM 1276

int n, m;
int a[MAXN][MAXN];
int f[MAXN][MAXM][MAXN];

int main() {
    // 读取输入
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // 动态规划求解
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= j; k++) {
                f[i][j][k] = 0;
                for (int l = 0; l <= k; l++) {
                    if (j - k >= l) {
                        f[i][j][k] = f[i][j][k] > f[i-1][j-k][l] + a[i][k-l+1] ? f[i][j][k] : f[i-1][j-k][l] + a[i][k-l+1];
                    }
                }
            }
        }
    }

    // 找到最大值
    int ans = 0;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= i; j++) {
            ans = ans > f[n][m][i] ? ans : f[n][m][i];
        }
    }

    // 输出结果
    printf("%d\n", ans);
    return 0;
}