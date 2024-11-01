#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义比较函数
int compare(const void *a, const void *b) {
    char strA[20], strB[20];
    sprintf(strA, "%d%d", *(int *)a, *(int *)b);
    sprintf(strB, "%d%d", *(int *)b, *(int *)a);
    return strcmp(strB, strA);
}

int main() {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // 使用自定义比较函数进行排序
    qsort(arr, n, sizeof(int), compare);

    // 输出结果
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}