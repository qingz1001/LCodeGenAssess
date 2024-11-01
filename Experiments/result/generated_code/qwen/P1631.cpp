#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int N;
    scanf("%d", &N);
    int A[N], B[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &B[i]);
    }

    // 计算所有可能的和并存储在一个数组中
    int sums[N*N];
    int index = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sums[index++] = A[i] + B[j];
        }
    }

    // 对所有和进行排序
    qsort(sums, N*N, sizeof(int), compare);

    // 输出前N个最小的和
    for (int i = 0; i < N; i++) {
        printf("%d ", sums[i]);
    }
    printf("\n");

    return 0;
}