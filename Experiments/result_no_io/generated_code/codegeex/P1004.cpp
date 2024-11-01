#include <stdio.h>

int n, a[10][10], f[20][10][10], ans;

int main() {
    scanf("%d", &n);
    while (1) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        if (x == 0 && y == 0 && z == 0) break;
        a[x][y] = z;
    }

    // 初始化动态规划数组
    for (int k = 2; k <= 18; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                f[k][i][j] = -1;
            }
        }
    }

    // 从起点开始走两条路径
    f[2][1][1] = a[1][1];

    // 动态规划计算两条路径的最大值
    for (int k = 3; k <= 18; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i > 1) f[k][i][j] = f[k-1][i-1][j];
                if (j > 1) f[k][i][j] = f[k][i][j] > f[k-1][i][j-1] ? f[k][i][j] : f[k-1][i][j-1];
                if (i < n) f[k][i][j] = f[k][i][j] > f[k-1][i+1][j] ? f[k][i][j] : f[k-1][i+1][j];
                if (j < n) f[k][i][j] = f[k][i][j] > f[k-1][i][j+1] ? f[k][i][j] : f[k-1][i][j+1];
                f[k][i][j] += a[i][j];
            }
        }
    }

    // 找出两条路径的最大值
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (f[18][i][j] > ans) ans = f[18][i][j];
        }
    }

    printf("%d", ans);
    return 0;
}