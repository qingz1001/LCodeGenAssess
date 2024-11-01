#include <stdio.h>
#include <math.h>

#define MOD 10007

long long fast_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    long long a[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    long long result = a[0];
    for (int i = 1; i < n; i++) {
        result = fast_pow(result, a[i], MOD);
    }

    printf("%lld\n", result);
    return 0;
}