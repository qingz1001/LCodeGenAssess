#include <stdio.h>

#define MOD 100000000

// 计算最大公约数
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 计算斐波那契数列的第n项
void fib(long long n, long long *result) {
    if (n <= 1) {
        result[0] = n;
        result[1] = 0;
        return;
    }
    
    long long a = 0, b = 1, c;
    for (long long i = 2; i <= n; i++) {
        c = (a + b) % MOD;
        a = b;
        b = c;
    }
    result[0] = b;
    result[1] = a;
}

int main() {
    long long n, m;
    scanf("%lld %lld", &n, &m);
    
    long long fn[2], fm[2];
    fib(n, fn);
    fib(m, fm);
    
    long long result = gcd(fn[0], fm[0]) % MOD;
    printf("%lld\n", result);
    
    return 0;
}