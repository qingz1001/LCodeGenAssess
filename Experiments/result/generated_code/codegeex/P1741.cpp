#include <stdio.h>
#include <string.h>

int main() {
    int n, i, j, k, ans = 0;
    char a[1000][1000];

    // 输入菱形的边长
    scanf("%d", &n);

    // 输入菱形上半部分
    for (i = 0; i < n; i++) {
        scanf("%s", a[i]);
    }

    // 输入菱形下半部分
    for (i = n; i < 2 * n; i++) {
        scanf("%s", a[i]);
    }

    // 遍历菱形网格，寻找满足条件的平行四边形
    for (i = 0; i < 2 * n; i++) {
        for (j = 0; j < 2 * n; j++) {
            if (a[i][j] == ' ') continue; // 如果当前格子不存在边，跳过

            // 检查以 (i, j) 为顶点的平行四边形
            for (k = 1; k + i < 2 * n && k + j < 2 * n; k++) {
                // 检查平行四边形的四个顶点是否存在边
                if (a[i][j] == a[i + k][j + k] && a[i][j] == a[i + k][j] && a[i][j] == a[i][j + k]) {
                    ans++;
                }
            }
        }
    }

    // 输出满足条件的平行四边形个数
    printf("%d\n", ans);

    return 0;
}