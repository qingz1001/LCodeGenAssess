#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100005

int r, c, n, m, a[N], b[N], c[N], d[N], x[N], y[N], k[N], s, ans;
char op[N];

int main() {
    // 读取棋盘的行数和列数
    scanf("%d%d", &r, &c);
    // 读取不同颜色的数量
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        // 读取每种颜色的两个棋子的坐标
        scanf("%d%d%d%d", &a[i], &b[i], &c[i], &d[i]);
        // 将棋子坐标转换为一维索引
        a[i] = (a[i] - 1) * c + b[i];
        c[i] = (c[i] - 1) * c + d[i];
    }
    // 读取操作的数量
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        // 读取操作的具体信息
        scanf("%d%d %c %c", &x[i], &y[i], &op[i], &op[i + m]);
        // 将操作坐标转换为一维索引
        x[i] = (x[i] - 1) * c + y[i];
    }

    // 对所有棋子和操作进行排序
    for (int i = 1; i <= n; i++) {
        a[i] *= 100;
        c[i] *= 100;
    }
    for (int i = 1; i <= m; i++) {
        x[i] *= 100;
    }
    qsort(a + 1, n, sizeof(int), (int (*)(const void *, const void *))strcmp);
    qsort(c + 1, n, sizeof(int), (int (*)(const void *, const void *))strcmp);
    qsort(x + 1, m, sizeof(int), (int (*)(const void *, const void *))strcmp);

    // 遍历所有棋子，计算能消去的棋子数量
    for (int i = 1, j = 1; i <= n; i++) {
        if (a[i] == c[i]) continue;
        while (j <= m && x[j] < a[i]) {
            if (op[j] == 'U') k[j]++;
            else if (op[j] == 'D') k[j + m]++;
            else if (op[j] == 'L') k[j + 2 * m]++;
            else if (op[j] == 'R') k[j + 3 * m]++;
            j++;
        }
        s += k[j - 1] * (k[j - 1] - 1) / 2;
        if (a[i] < c[i]) {
            ans = k[j - 1];
            k[j - 1] = 0;
        } else {
            k[j - 1] = 0;
            ans = k[j - 1];
        }
    }

    // 输出结果
    printf("%d %d\n", s, ans);
    return 0;
}