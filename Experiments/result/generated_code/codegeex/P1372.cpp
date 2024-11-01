#include <stdio.h>

// 计算两个数的最大公约数
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    // 最大默契值即为 k 和 n 的最大公约数
    printf("%d\n", gcd(n, k));

    return 0;
}