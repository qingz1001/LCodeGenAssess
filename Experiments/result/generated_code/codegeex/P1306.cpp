#include <stdio.h>

long long fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = (a + b) % 100000000;
        a = b;
        b = c;
    }
    return b;
}

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    long long fn = fibonacci(n);
    long long fm = fibonacci(m);
    printf("%d\n", gcd(fn, fm));
    return 0;
}