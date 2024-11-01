#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int arr[3];
    scanf("%d %d %d", &arr[0], &arr[1], &arr[2]);

    // 对数组进行排序
    qsort(arr, 3, sizeof(int), compare);

    // 计算等差数列的公差
    int d = arr[1] - arr[0];

    // 计算第四个数
    int fourth = arr[2] + d;

    printf("%d\n", fourth);

    return 0;
}