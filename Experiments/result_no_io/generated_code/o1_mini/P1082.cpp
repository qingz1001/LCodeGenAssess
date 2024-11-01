#include <stdio.h>

long long extended_gcd_func(long long a, long long b, long long* x, long long* y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long long x1, y1;
    long long g = extended_gcd_func(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}

int main(){
    long long a, b;
    scanf("%lld %lld", &a, &b);
    long long x, y;
    extended_gcd_func(a, b, &x, &y);
    long long x0 = x % b;
    if (x0 <= 0) x0 += b;
    printf("%lld\n", x0);
    return 0;
}