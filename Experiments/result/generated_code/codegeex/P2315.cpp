#include <stdio.h>

int n;
int a[55][55];

int main() {
    int i, j, k, t, ans = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= i; j++)
            scanf("%d", &a[i][j]);

    // 统计每个点的上边和右边连续1的个数
    for (i = 1; i <= n; i++)
        for (j = 1; j <= i; j++) {
            if (a[i][j]) {
                t = 1;
                while (a[i][j + t]) t++;
                a[i][j] = t;
                t = 1;
                while (a[i - 1][j + t]) t++;
                a[i][j] += t - 1;
            }
        }

    // 统计每个点的下边和左边连续1的个数
    for (i = n; i >= 1; i--)
        for (j = 1; j <= i; j++) {
            if (a[i][j]) {
                t = 1;
                while (a[i][j - t]) t++;
                a[i][j] += t - 1;
                t = 1;
                while (a[i - 1][j - t]) t++;
                a[i][j] += t - 1;
                ans += a[i][j] - 3;
            }
        }

    printf("%d\n", ans);
    return 0;
}