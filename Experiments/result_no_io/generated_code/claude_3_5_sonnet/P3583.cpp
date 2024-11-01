#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 1000000000000000000LL

long long k(long long n) {
    long long i, j, sum;
    for (i = 1; i * i <= n; i++) {
        sum = 0;
        for (j = i; j >= 1; j--) {
            if (sum + j * j <= n) {
                sum += j * j;
            }
        }
        if (sum == n) {
            return i;
        }
    }
    return -1;
}

int is_superweighty(long long x) {
    long long kx = k(x);
    if (kx == -1) return 0;
    for (long long y = x + 1; y <= x + kx * kx; y++) {
        if (k(y) < kx) {
            return 1;
        }
    }
    return 0;
}

int main() {
    long long n;
    scanf("%lld", &n);

    long long kn = k(n);
    if (kn == -1) {
        printf("- ");
    } else {
        printf("%lld ", kn);
    }

    long long count = 0;
    for (long long i = 1; i <= n; i++) {
        if (is_superweighty(i)) {
            count++;
        }
    }
    printf("%lld\n", count);

    return 0;
}