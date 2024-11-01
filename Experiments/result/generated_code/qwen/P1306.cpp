#include <stdio.h>

#define MOD 100000000

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int fibonacci(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = (a + b) % MOD;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int fn = fibonacci(n), fm = fibonacci(m);
    printf("%d\n", gcd(fn, fm));
    return 0;
}