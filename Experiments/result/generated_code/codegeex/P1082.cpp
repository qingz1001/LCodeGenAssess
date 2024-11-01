#include <stdio.h>

int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    
    // 使用扩展欧几里得算法求 a 和 b 的最大公约数，并求出 x 和 y
    int x = 0, y = 0;
    int gcd = extended_gcd(a, b, &x, &y);
    
    // 由于题目保证一定有解，所以 gcd 应该为 1
    // 输出最小正整数解
    printf("%d\n", (x % b + b) % b);
    
    return 0;
}

// 扩展欧几里得算法
int extended_gcd(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    
    int x1, y1;
    int gcd = extended_gcd(b, a % b, &x1, &y1);
    
    *x = y1;
    *y = x1 - (a / b) * y1;
    
    return gcd;
}