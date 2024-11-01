#include <stdio.h>

#define N 100005

int x[N], t[N], a, b, c, d, n, m, q, u, v;

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int main() {
    // 读取随机数生成器的种子和参数
    scanf("%d%d%d%d%d", &x[0], &a, &b, &c, &d);
    
    // 生成随机数序列
    for (int i = 1; i <= n * m; i++) {
        x[i] = (1ll * a * x[i - 1] * x[i - 1] + 1ll * b * x[i - 1] + c) % d;
    }
    
    // 初始化排列
    for (int i = 1; i <= n * m; i++) {
        t[i] = i;
    }
    
    // 进行初始的 n * m 次交换操作
    for (int i = 1; i <= n * m; i++) {
        swap(&t[i], &t[(x[i] % i) + 1]);
    }
    
    // 读取额外的交换操作次数
    scanf("%d", &q);
    
    // 进行额外的 q 次交换操作
    for (int i = 1; i <= q; i++) {
        scanf("%d%d", &u, &v);
        swap(&t[u], &t[v]);
    }
    
    // 输出字典序最小的路径序列
    int row = 1, col = 1;
    while (row != n || col != m) {
        printf("%d ", t[(row - 1) * m + col]);
        if (row == n) {
            col++;
        } else if (col == m) {
            row++;
        } else if (t[(row - 1) * m + col] < t[row * m + col - 1]) {
            col++;
        } else {
            row++;
        }
    }
    printf("%d\n", t[(n - 1) * m + m - 1]);
    
    return 0;
}