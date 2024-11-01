#include <stdio.h>

int main() {
    int a, n, m, x;
    scanf("%d %d %d %d", &a, &n, &m, &x);

    int on = a; // 当前站上车人数
    int off = 0; // 当前站下车人数
    int current = a; // 当前站车上人数

    for (int i = 2; i <= n - 1; i++) {
        off = on;
        on = on + off;
        if (i == x) {
            printf("%d\n", current);
            return 0;
        }
        current += on - off;
    }

    printf("%d\n", current);
    return 0;
}