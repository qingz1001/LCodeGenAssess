#include <stdio.h>
#include <math.h>

#define MAXN 1000000000LL

long long k(long long n) {
    if (n == 1) return 1;
    for (long long i = sqrt(n); i >= 1; i--) {
        if (n % i == 0) {
            long long quotient = n / i;
            if (quotient != i && quotient - i <= 1) {
                return i;
            }
            long long res = k(quotient);
            if (res != -1 && i < res) {
                return i;
            }
        }
    }
    return -1;
}

int main() {
    long long n;
    scanf("%lld", &n);

    long long result1 = k(n);
    long long result2 = 0;

    if (result1 == -1) {
        printf("- ");
    } else {
        printf("%lld ", result1);
    }

    for (long long i = 1; i <= n; i++) {
        if (k(i) < k(i - 1)) {
            result2++;
        }
    }

    printf("%lld\n", result2);

    return 0;
}