#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_NUM 1000

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int N, numbers[MAX_N], unique[MAX_N], count = 0;
    int i, j;

    // 读取输入
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &numbers[i]);
    }

    // 排序
    qsort(numbers, N, sizeof(int), cmp);

    // 去重
    unique[0] = numbers[0];
    count = 1;
    for (i = 1; i < N; i++) {
        if (numbers[i] != numbers[i-1]) {
            unique[count++] = numbers[i];
        }
    }

    // 输出结果
    printf("%d\n", count);
    for (i = 0; i < count; i++) {
        printf("%d", unique[i]);
        if (i < count - 1) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}