#include <stdio.h>

int main() {
    int k, m, n;
    scanf("%d %d %d", &k, &m, &n);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        // 判断当前技能是否可以杀死 boss
        if (b > 0 && k * b >= n) {
            printf("%d ", i + 1);
        }
    }

    // 如果没有找到可以杀死 boss 的技能
    if (m > 0 && printf("\n") == 0) {
        printf("-1\n");
    }

    return 0;
}