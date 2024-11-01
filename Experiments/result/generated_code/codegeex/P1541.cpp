#include <stdio.h>
#include <string.h>

int n, m, a[360], f[360][130][130][130][130], b[130];

int main() {
    // 读取输入
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &b[i]);

    // 初始化动态规划数组
    memset(f, -1, sizeof(f));
    f[0][0][0][0][0] = a[1];

    // 动态规划求解
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= 40; j++) {
            for (int k = 0; k <= 40; k++) {
                for (int l = 0; l <= 40; l++) {
                    for (int p = 0; p <= 40; p++) {
                        if (f[i][j][k][l][p] != -1) {
                            if (j + 1 <= 40 && i + 1 <= m && b[i + 1] == 1) f[i + 1][j + 1][k][l][p] = f[i][j][k][l][p] + a[i + 2];
                            if (k + 1 <= 40 && i + 1 <= m && b[i + 1] == 2) f[i + 1][j][k + 1][l][p] = f[i][j][k][l][p] + a[i + 3];
                            if (l + 1 <= 40 && i + 1 <= m && b[i + 1] == 3) f[i + 1][j][k][l + 1][p] = f[i][j][k][l][p] + a[i + 4];
                            if (p + 1 <= 40 && i + 1 <= m && b[i + 1] == 4) f[i + 1][j][k][l][p + 1] = f[i][j][k][l][p] + a[i + 5];
                        }
                    }
                }
            }
        }
    }

    // 找到最大得分
    int ans = 0;
    for (int i = 0; i <= 40; i++)
        for (int j = 0; j <= 40; j++)
            for (int k = 0; k <= 40; k++)
                for (int l = 0; l <= 40; l++)
                    ans = (ans > f[m][i][j][k][l]) ? ans : f[m][i][j][k][l];

    // 输出结果
    printf("%d\n", ans);
    return 0;
}