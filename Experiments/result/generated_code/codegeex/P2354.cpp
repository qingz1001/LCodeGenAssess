#include <stdio.h>

int main() {
    int x0, a, b, c, d, n, m, q, u, v, t[1000001], x[1000001];
    int i, j, k;

    // 读取输入
    scanf("%d%d%d%d%d", &x0, &a, &b, &c, &d);
    scanf("%d%d%d", &n, &m, &q);

    // 初始化随机数生成器
    x[0] = x0;
    for (i = 1; i <= n * m; i++) {
        x[i] = (1ll * a * x[i-1] * x[i-1] + 1ll * b * x[i-1] + c) % d;
    }

    // 初始化排列
    for (i = 1; i <= n * m; i++) {
        t[i] = i;
    }

    // 进行初始交换操作
    for (i = 1; i <= n * m; i++) {
        j = (x[i-1] % i) + 1;
        k = t[i];
        t[i] = t[j];
        t[j] = k;
    }

    // 进行额外交换操作
    for (i = 1; i <= q; i++) {
        scanf("%d%d", &u, &v);
        k = t[u];
        t[u] = t[v];
        t[v] = k;
    }

    // 输出字典序最小的路径序列
    i = 1;
    j = 1;
    while (i <= n && j <= m) {
        printf("%d ", t[(i-1) * m + j]);
        if (t[(i-1) * m + j] < t[(i-1) * m + j+1] && t[(i-1) * m + j] < t[i * m + j-1]) {
            i++;
        } else if (t[(i-1) * m + j] > t[(i-1) * m + j+1] && t[(i-1) * m + j] < t[i * m + j-1]) {
            j++;
        } else {
            if (t[(i-1) * m + j+1] < t[i * m + j-1]) {
                j++;
            } else {
                i++;
            }
        }
    }
    while (i <= n) {
        printf("%d ", t[(i-1) * m + m]);
        i++;
    }
    while (j <= m) {
        printf("%d ", t[(n-1) * m + j]);
        j++;
    }

    return 0;
}