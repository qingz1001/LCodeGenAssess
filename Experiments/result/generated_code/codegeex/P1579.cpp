#include <stdio.h>

// 函数用于判断一个数是否为质数
int isPrime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);

    // 从最小的质数开始尝试
    for (int i = 2; i <= n / 3; i++) {
        if (isPrime(i)) {
            // 第二个质数
            for (int j = i; j <= n / 2; j++) {
                if (isPrime(j) && isPrime(n - i - j)) {
                    printf("%d %d %d\n", i, j, n - i - j);
                    return 0;
                }
            }
        }
    }
    return 0;
}