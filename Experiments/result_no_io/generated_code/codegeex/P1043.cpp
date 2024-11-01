#include <stdio.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    
    int a[55];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    // 首尾相接
    a[n + 1] = a[1];
    
    // 计算最大值
    int max = 0;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            sum += a[(i + j) % (n + 1)];
        }
        max = (max * 10 + sum) % 10;
    }
    
    // 计算最小值
    int min = 1;
    for (int i = 0; i < m; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            sum += a[(i + j) % (n + 1)];
        }
        min = (min * (sum % 10)) % 10;
    }
    
    printf("%d\n%d\n", min, max);
    
    return 0;
}