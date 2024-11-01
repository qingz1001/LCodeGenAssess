#include <stdio.h>
#include <string.h>

int n, m;
int a[2010][2010], b[2010][2010], c[2010][2010], d[2010][2010];
int max1, max2;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // 计算每行和每列的连续黑白相间长度
    for (int i = 1; i <= n; i++) {
        int sum = 0;
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == a[i][j - 1]) {
                sum = 0;
            } else {
                sum++;
            }
            b[i][j] = sum;
        }
        sum = 0;
        for (int j = m; j >= 1; j--) {
            if (a[i][j] == a[i][j + 1]) {
                sum = 0;
            } else {
                sum++;
            }
            c[i][j] = sum;
        }
    }

    for (int j = 1; j <= m; j++) {
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i][j] == a[i - 1][j]) {
                sum = 0;
            } else {
                sum++;
            }
            d[i][j] = sum;
        }
        sum = 0;
        for (int i = n; i >= 1; i--) {
            if (a[i][j] == a[i + 1][j]) {
                sum = 0;
            } else {
                sum++;
            }
            sum = sum > d[i][j] ? sum : d[i][j];
            d[i][j] = sum;
        }
    }

    // 计算最大正方形和最大矩形面积
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int min = b[i][j] < c[i][j] ? b[i][j] : c[i][j];
            min = min < d[i][j] ? min : d[i][j];
            max1 = max1 > min ? max1 : min;
            max2 = max2 > b[i][j] * d[i][j] ? max2 : b[i][j] * d[i][j];
            max2 = max2 > c[i][j] * d[i][j] ? max2 : c[i][j] * d[i][j];
        }
    }

    printf("%d\n%d\n", max1 * max1, max2);
    return 0;
}