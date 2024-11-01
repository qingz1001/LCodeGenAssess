#include <stdio.h>
#include <stdlib.h>

#define MAXN 3100000
#define MAXD 1000000

int main() {
    int P;
    scanf("%d", &P);

    // 计算 2^P - 1 的位数
    long long bits = (long long)P * __builtin_clzll(1LL << (P - 1)) + 1;

    // 计算 2^P - 1 的最后 500 位数字
    int last_500[500];
    for (int i = 0; i < 500; i++) {
        last_500[i] = 0;
    }
    for (int i = 0; i < P; i++) {
        int carry = 0;
        for (int j = 0; j < 500; j++) {
            long long temp = (long long)last_500[j] * 2 + carry;
            last_500[j] = temp % 10;
            carry = temp / 10;
        }
    }

    // 输出结果
    printf("%lld\n", bits);
    for (int i = 499; i >= 0; i--) {
        if (i % 50 == 0 && i != 499) {
            printf("\n");
        }
        printf("%d", last_500[i]);
    }
    printf("\n");

    return 0;
}