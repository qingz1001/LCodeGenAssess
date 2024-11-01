#include <stdio.h>
#include <stdlib.h>

int main() {
    long long N, M;
    scanf("%lld %lld", &N, &M);

    // 计算每个数的基础值
    long long base = N / M;
    long long remainder = N % M;

    // 初始化结果数组
    for (long long i = 0; i < M; i++) {
        printf("%lld ", base);
    }

    // 分配余数到前几个数
    for (long long i = 0; i < remainder; i++) {
        printf("1 ");
    }

    return 0;
}