#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_NUM 1000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int N, numbers[MAX_N], unique[MAX_N];
    int count = 0;

    // 读取输入
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &numbers[i]);
    }

    // 排序
    qsort(numbers, N, sizeof(int), compare);

    // 去重
    unique[0] = numbers[0];
    count = 1;
    for (int i = 1; i < N; i++) {
        if (numbers[i] != numbers[i-1]) {
            unique[count] = numbers[i];
            count++;
        }
    }

    // 输出结果
    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d ", unique[i]);
    }
    printf("\n");

    return 0;
}