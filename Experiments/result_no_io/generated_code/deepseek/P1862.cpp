#include <stdio.h>
#include <stdlib.h>

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n;
    scanf("%d", &n);
    
    int *y_coords = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        y_coords[i] = y;
    }
    
    // 对y坐标进行排序
    qsort(y_coords, n, sizeof(int), compare);
    
    // 最优主管道的位置是y坐标的中位数
    int median_y = y_coords[n / 2];
    
    // 计算最小长度总和
    int total_length = 0;
    for (int i = 0; i < n; i++) {
        total_length += abs(y_coords[i] - median_y);
    }
    
    printf("%d\n", total_length);
    
    free(y_coords);
    return 0;
}