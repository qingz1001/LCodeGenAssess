#include <stdio.h>
#include <stdlib.h>

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n;
    scanf("%d", &n);
    int T[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &T[i]);
    }

    // 按接水时间从小到大排序
    qsort(T, n, sizeof(int), compare);

    // 输出排序后的顺序
    for (int i = 0; i < n; i++) {
        printf("%d ", T[i]);
    }
    printf("\n");

    // 计算平均等待时间
    double total_wait_time = 0;
    for (int i = 0; i < n; i++) {
        total_wait_time += T[i] * (n - i - 1);
    }
    double average_wait_time = total_wait_time / n;

    // 输出平均等待时间，保留两位小数
    printf("%.2f\n", average_wait_time);

    return 0;
}