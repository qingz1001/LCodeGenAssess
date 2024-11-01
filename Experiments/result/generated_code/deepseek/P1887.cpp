#include <stdio.h>

void findMaxProduct(int N, int M) {
    int result[M];
    int remaining = N;

    // 初始化所有数为1
    for (int i = 0; i < M; i++) {
        result[i] = 1;
    }

    // 从后往前尽可能分配剩余的值
    for (int i = M - 1; i >= 0; i--) {
        if (remaining > 0) {
            int add = remaining / (i + 1);
            result[i] += add;
            remaining -= add;
        }
    }

    // 输出结果
    for (int i = 0; i < M; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    findMaxProduct(N, M);
    return 0;
}