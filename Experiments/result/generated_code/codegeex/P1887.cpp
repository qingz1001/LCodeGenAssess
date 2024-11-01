#include <stdio.h>

int main() {
    long long N, M;
    scanf("%lld %lld", &N, &M);

    // 初始时每个数为1，乘积最大
    long long arr[M];
    for (int i = 0; i < M; i++) {
        arr[i] = 1;
    }

    // 剩余的数平均分配给前面的M-1个数
    long long remainder = N - M;
    for (int i = 0; i < M - 1; i++) {
        if (remainder > 0) {
            arr[i]++;
            remainder--;
        } else {
            break;
        }
    }

    // 输出结果
    for (int i = 0; i < M; i++) {
        printf("%lld ", arr[i]);
    }
    printf("\n");

    return 0;
}