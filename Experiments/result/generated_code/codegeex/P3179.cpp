#include <stdio.h>

int main() {
    int n, k, w, x;
    scanf("%d %d", &n, &k);
    while (k--) {
        scanf("%d", &w);
        int count = 0;
        for (int i = 0; i < w; i++) {
            scanf("%d", &x);
            // 计算每个白色格子的约数个数
            for (int j = 1; j * j <= x; j++) {
                if (x % j == 0) {
                    count += 2;
                    if (j * j == x) count--; // 去除重复的平方根
                }
            }
        }
        // 判断先手是否必胜
        if (count % 2 == 1) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}