#include <stdio.h>

long long exgcd(long long a, long long b, long long *x, long long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long long d = exgcd(b, a % b, y, x);
    *y -= (a / b) * (*x);
    return d;
}

int main() {
    long long a, b, x, y;
    scanf("%lld %lld", &a, &b);
    
    long long d = exgcd(a, b, &x, &y);
    
    // 确保x为正数
    x = (x % b + b) % b;
    
    printf("%lld\n", x);
    
    return 0;
}