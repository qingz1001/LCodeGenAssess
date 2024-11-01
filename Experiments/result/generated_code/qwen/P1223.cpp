#include <stdio.h>
#include <stdlib.h>

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    scanf("%d", &n);
    int times[n];
    
    // 读取每个人的接水时间
    for (int i = 0; i < n; i++) {
        scanf("%d", &times[i]);
    }
    
    // 对接水时间进行排序
    qsort(times, n, sizeof(int), compare);
    
    // 输出最优排队顺序
    printf("1");
    for (int i = 2; i <= n; i++) {
        printf(" %d", i);
    }
    printf("\n");
    
    // 计算并输出平均等待时间
    double total_wait_time = 0;
    for (int i = 0; i < n; i++) {
        total_wait_time += (double)(i + 1) * times[i];
    }
    double average_wait_time = total_wait_time / n;
    printf("%.2f\n", average_wait_time);
    
    return 0;
}