#include <stdio.h>

int main() {
    int n, m, type;
    scanf("%d %d %d", &n, &m, &type);

    int t[101], q[101];
    int count = 0; // 记录既乘车又打狼的人数

    for (int i = 0; i < n; i++) {
        scanf("%d", &t[i]);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &q[i]);
        if (t[i] == 1 && q[i] == 1) {
            count++;
        }
    }

    int bottles = 0;
    if (count >= m) {
        bottles = n - count + m;
    } else {
        bottles = n;
    }

    printf("%d\n", bottles);
    return 0;
}