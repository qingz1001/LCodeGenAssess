#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    
    // 读取数组元素
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    // 计算最少操作次数
    int operations = 0;
    int current_value = 0;
    
    for (int i = 0; i < n; i++) {
        if (a[i] != current_value) {
            operations++;
            current_value = a[i];
        }
    }
    
    // 输出结果
    printf("%d\n", operations);
    
    return 0;
}