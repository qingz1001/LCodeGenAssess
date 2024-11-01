#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    long long b[1001];

    // 读取经过操作后的序列
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &b[i]);
    }

    // 读取操作并逆操作
    for (int i = 1; i <= m; i++) {
        int k, x, y;
        scanf("%d %d %d", &k, &x, &y);

        if (k == 1) {
            // 逆操作：1 x y 表示第 x 个元素加上第 y 个元素
            if (x == y) {
                b[x] /= 2;
            } else {
                b[x] -= b[y];
            }
        } else if (k == 2) {
            // 逆操作：2 x y 表示第 x 个元素乘上第 y 个元素
            if (x == y) {
                b[x] = (long long)sqrt(b[x]);
            } else {
                b[x] /= b[y];
            }
        }
    }

    // 输出序列最初的形态
    for (int i = 1; i <= n; i++) {
        printf("%lld ", b[i]);
    }
    printf("\n");

    return 0;
}