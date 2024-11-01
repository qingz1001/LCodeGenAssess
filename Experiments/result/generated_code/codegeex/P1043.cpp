#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    // 计算所有数字的总和
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    
    // 计算每部分的最小值和最大值
    int min_val = 0, max_val = 0;
    for (int i = 0; i < m - 1; i++) {
        min_val = (min_val + a[i]) % 10;
        max_val = (max_val + a[i]) % 10;
    }
    
    // 计算剩余部分的和
    int remaining_sum = sum;
    for (int i = 0; i < m - 1; i++) {
        remaining_sum -= a[i];
    }
    
    // 计算最小值和最大值
    min_val = (min_val + remaining_sum) % 10;
    max_val = (max_val + remaining_sum) % 10;
    
    // 输出结果
    printf("%d\n%d\n", min_val, max_val);
    
    free(a);
    return 0;
}