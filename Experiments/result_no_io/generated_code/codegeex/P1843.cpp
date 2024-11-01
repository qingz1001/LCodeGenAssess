#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    
    int *clothes = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &clothes[i]);
    }
    
    // 使用快速排序对湿度进行排序
    qsort(clothes, n, sizeof(int), compare);
    
    int time = 0;
    while (clothes[0] > 0) {
        time++;
        for (int i = 0; i < n && clothes[i] > 0; i++) {
            clothes[i] -= a;
            if (clothes[i] <= 0) {
                clothes[i] = 0;
                break;
            }
        }
        // 检查是否还有剩余的湿度需要烘干
        if (clothes[0] > 0) {
            for (int i = 0; i < n && clothes[i] > 0; i++) {
                clothes[i] -= b;
            }
        }
    }
    
    printf("%d\n", time);
    free(clothes);
    return 0;
}

// 比较函数，用于快速排序
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}