#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    if (n < 1 || n > 1000) {
        printf("Invalid input\n");
        return 1;
    }

    int min_coins = 0;
    int count = 0;

    // 计算最少需要的硬币数
    for (int i = 1; i <= n; i *= 2) {
        min_coins++;
    }

    // 计算最少硬币数的组成方案个数
    if (n == 1) {
        count = 1;
    } else if (n == 2) {
        count = 1;
    } else if (n == 3) {
        count = 2;
    } else {
        count = 2; // 对于 n >= 4，最少需要 3 个硬币，且有两种方法
    }

    printf("%d %d\n", min_coins, count);

    return 0;
}