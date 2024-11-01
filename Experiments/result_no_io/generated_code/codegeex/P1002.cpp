#include <stdio.h>

int n, m, x, y;
int f[21][21];

int main() {
    // 读取输入
    scanf("%d%d%d%d", &n, &m, &x, &y);

    // 初始化棋盘
    f[0][0] = 1;

    // 遍历棋盘
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            // 如果当前位置不是马的控制的点
            if ((i != x && j != y) && (i - 2 >= 0 && j - 1 >= 0) && (i - 1 >= 0 && j - 2 >= 0)) {
                f[i][j] = f[i - 1][j] + f[i][j - 1] - f[i - 2][j - 1] - f[i - 1][j - 2];
            } else {
                f[i][j] = f[i - 1][j] + f[i][j - 1];
            }
        }
    }

    // 输出结果
    printf("%d\n", f[n][m]);

    return 0;
}