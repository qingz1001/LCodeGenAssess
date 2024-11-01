#include <stdio.h>

int main() {
    long long N, K;
    scanf("%lld %lld", &N, &K);

    // 计算初始瓶子数量和目标瓶子数量的差值
    long long difference = N - K;

    // 如果初始瓶子数量小于等于目标瓶子数量，则不需要新瓶子
    if (difference <= 0) {
        printf("0\n");
    } else {
        // 计算最少需要买的新瓶子数量
        long long newBottles = 0;
        for (long long i = 1; i <= difference; i++) {
            newBottles += i;
        }
        printf("%lld\n", newBottles);
    }

    return 0;
}