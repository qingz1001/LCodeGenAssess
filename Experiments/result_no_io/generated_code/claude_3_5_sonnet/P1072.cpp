#include <stdio.h>

long long gcd(long long a, long long b) {
    return b ? gcd(b, a % b) : a;
}

long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}

int solve(long long a0, long long a1, long long b0, long long b1) {
    if (b1 % b0 != 0 || a0 % a1 != 0) return 0;
    
    long long x = lcm(a1, b0);
    if (x % a1 != 0 || b1 % x != 0) return 0;
    
    long long start = x, end = b1;
    int count = 0;
    
    for (long long i = start; i <= end; i += x) {
        if (gcd(i, a0) == a1 && lcm(i, b0) == b1) {
            count++;
        }
    }
    
    return count;
}

int main() {
    int n;
    scanf("%d", &n);
    
    while (n--) {
        long long a0, a1, b0, b1;
        scanf("%lld %lld %lld %lld", &a0, &a1, &b0, &b1);
        printf("%d\n", solve(a0, a1, b0, b1));
    }
    
    return 0;
}