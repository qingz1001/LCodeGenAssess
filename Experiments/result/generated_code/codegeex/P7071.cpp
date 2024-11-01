#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    // 判断 n 是否为 2 的正整数次幂
    if ((n & (n - 1)) != 0) {
        printf("-1\n");
        return 0;
    }

    // 从大到小输出 n 的拆分
    while (n > 0) {
        int maxPower = 1;
        // 找到最大的 2 的正整数次幂
        while (maxPower <= n) {
            maxPower <<= 1;
        }
        maxPower >>= 1;
        printf("%d ", maxPower);
        n -= maxPower;
    }

    return 0;
}