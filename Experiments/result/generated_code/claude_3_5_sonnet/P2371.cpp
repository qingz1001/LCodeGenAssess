#include <stdio.h>
#include <stdlib.h>

#define MAX_N 12
#define MAX_A 500000

long long gcd(long long a, long long b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    int n, a[MAX_N];
    long long l, r, g = 0;

    scanf("%d %lld %lld", &n, &l, &r);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        g = gcd(g, a[i]);
    }

    long long start = (l + g - 1) / g * g;
    long long end = r / g * g;

    if (start > end) {
        printf("0\n");
    } else {
        printf("%lld\n", (end - start) / g + 1);
    }

    return 0;
}