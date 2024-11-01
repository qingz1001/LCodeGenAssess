#include <stdio.h>

int main() {
    int n, a, b, g, k, x, y;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &a, &b, &g, &k);
        scanf("%d%d", &x, &y);

        // 判断点 (x, y) 是否在地毯 i 的范围内
        if (x >= a && x <= a + g && y >= b && y <= b + k) {
            printf("%d\n", i);
            return 0;
        }
    }

    // 如果没有找到覆盖点 (x, y) 的地毯，输出 -1
    printf("-1\n");
    return 0;
}