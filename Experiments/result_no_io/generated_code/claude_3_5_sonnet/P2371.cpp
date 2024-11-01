#include <stdio.h>
#include <stdlib.h>

#define MAX_N 12
#define MAX_A 500000

long long gcd(long long a, long long b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    int n;
    long long l, r;
    scanf("%d %lld %lld", &n, &l, &r);

    int a[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    long long g = 0;
    for (int i = 0; i < n; i++) {
        g = gcd(g, a[i]);
    }

    long long start = (l + g - 1) / g * g;
    long long end = r / g * g;

    long long count = 0;
    if (start <= end) {
        count = (end - start) / g + 1;
    }

    printf("%lld\n", count);

    return 0;
}