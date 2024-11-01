#include <stdio.h>

#define MOD 1000000007
#define MAXN 10000001

long long a[MAXN];
long long inv[MAXN];

long long quick_pow(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = result * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return result;
}

void init_inv(int n) {
    inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
}

int main() {
    int n, A, B, C;
    scanf("%d%d%d%d%lld", &n, &A, &B, &C, &a[1]);

    for (int i = 2; i <= n; i++)
        a[i] = (a[i-1] * A + B) % 100000001;
    for (int i = 1; i <= n; i++)
        a[i] = a[i] % C + 1;

    init_inv(C);

    long long sum = 0;
    for (int i = 1; i <= n; i++)
        sum = (sum + inv[a[i]]) % MOD;

    long long result = sum * quick_pow(n, MOD-2) % MOD;

    printf("%.3f\n", (double)result / MOD * n);

    return 0;
}