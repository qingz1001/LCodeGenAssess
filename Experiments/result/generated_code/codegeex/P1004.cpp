#include <stdio.h>
#include <string.h>

int n, f[20][20][20][20], a[20][20];

int main() {
    scanf("%d", &n);
    int x, y, z;
    while (1) {
        scanf("%d%d%d", &x, &y, &z);
        if (x == 0 && y == 0 && z == 0) break;
        a[x][y] = z;
    }

    // 初始化边界条件
    for (int k1 = 0; k1 <= 2 * n; k1++) {
        for (int k2 = 0; k2 <= 2 * n; k2++) {
            for (int i = 0; i <= n; i++) {
                for (int j = 0; j <= n; j++) {
                    if (i == 0 && j == 0) {
                        f[i][j][k1][k2] = 0;
                    } else if (k1 == 0 && k2 == 0) {
                        f[i][j][k1][k2] = 0;
                    } else if (k1 == 0) {
                        f[i][j][k1][k2] = f[i][j-1][k1][k2-1] + a[i][j];
                    } else if (k2 == 0) {
                        f[i][j][k1][k2] = f[i-1][j][k1-1][k2] + a[i][j];
                    } else {
                        f[i][j][k1][k2] = f[i-1][j][k1-1][k2] + f[i][j-1][k1][k2-1] - f[i-1][j-1][k1-1][k2-1] + a[i][j];
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ans = f[i][j][2*n][2*n] > ans ? f[i][j][2*n][2*n] : ans;
        }
    }

    printf("%d\n", ans);
    return 0;
}