#include <stdio.h>

int main() {
    int n, m, type;
    scanf("%d %d %d", &n, &m, &type);

    int t[100], q[100];
    int count = 0;
    int total_bottles = 0;

    // 读取交通方式
    for (int i = 0; i < n; i++) {
        scanf("%d", &t[i]);
    }

    // 读取颓废值
    for (int i = 0; i < n; i++) {
        scanf("%d", &q[i]);
    }

    // 计算既乘坐大巴又愿意打狼的人数
    for (int i = 0; i < n; i++) {
        if (t[i] == 1 && q[i] == 1) {
            count++;
        }
    }

    // 计算快乐水总瓶数
    if (count >= m) {
        total_bottles = n - count + m;
    } else {
        total_bottles = n;
    }

    printf("%d\n", total_bottles);

    return 0;
}