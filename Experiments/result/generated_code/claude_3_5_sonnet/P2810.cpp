#include <stdio.h>
#include <stdlib.h>

long long solve(long long n) {
    long long m = 1;
    while (1) {
        long long count = 0;
        for (long long a = 1; a <= m; a++) {
            for (long long k = 2; k <= m / a; k++) {
                long long b = a * k;
                if (b > m) break;
                long long c = b * k;
                if (c > m) break;
                long long d = c * k;
                if (d > m) break;
                count++;
                if (count > n) return 0;
            }
        }
        if (count == n) return m;
        m++;
    }
}

int main() {
    long long n;
    scanf("%lld", &n);
    long long result = solve(n);
    if (result == 0) {
        printf("-1\n");
    } else {
        printf("%lld\n", result);
    }
    return 0;
}