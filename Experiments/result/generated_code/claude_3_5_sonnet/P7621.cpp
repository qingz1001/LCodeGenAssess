#include <stdio.h>

int main() {
    int n, b;
    double a, total = 0;
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%lf %d", &a, &b);
        total += a * b;
    }
    
    total *= 0.85;  // 打八五折
    
    // 将总金额转换为分
    int cents = (int)(total * 100 + 0.5);
    
    // 去掉多出的小于一角的零头
    cents = cents / 10 * 10;
    
    // 将分转换回元并输出
    printf("%.1f\n", cents / 100.0);
    
    return 0;
}