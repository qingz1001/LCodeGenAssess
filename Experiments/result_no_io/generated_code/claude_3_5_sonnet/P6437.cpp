#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int n, m;
    int numbers[MAX_N];
    
    // 读取输入
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }
    
    // 对数组进行降序排序
    qsort(numbers, n, sizeof(int), compare);
    
    int max_sum = 0;
    
    // 遍历所有可能的三个数字组合
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                int sum = numbers[i] + numbers[j] + numbers[k];
                if (sum <= m && sum > max_sum) {
                    max_sum = sum;
                }
                // 如果找到了最大和，直接返回结果
                if (max_sum == m) {
                    printf("%d\n", max_sum);
                    return 0;
                }
            }
        }
    }
    
    // 输出结果
    printf("%d\n", max_sum);
    
    return 0;
}