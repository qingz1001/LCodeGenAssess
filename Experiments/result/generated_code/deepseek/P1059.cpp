#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int N;
    scanf("%d", &N);
    int arr[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    // 先排序
    qsort(arr, N, sizeof(int), compare);

    // 去重
    int unique[N];
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (i == 0 || arr[i] != arr[i - 1]) {
            unique[count++] = arr[i];
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