#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int main() {
    int N, M;
    int A[MAX_N];
    int count = 0;
    long long sum = 0;

    // 读取输入
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    // 计算最少划分的段数
    for (int i = 0; i < N; i++) {
        if (sum + A[i] > M) {
            count++;
            sum = A[i];
        } else {
            sum += A[i];
        }
    }

    // 处理最后一段
    if (sum > 0) {
        count++;
    }

    // 输出结果
    printf("%d\n", count);

    return 0;
}