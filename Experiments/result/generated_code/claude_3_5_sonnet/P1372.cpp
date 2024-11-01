#include <stdio.h>

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

long long solve(long long n, long long k) {
    if (k == 1) return n;
    long long result = n / k;
    for (long long i = result; i >= 1; i--) {
        long long count = n / i - (n / (i + 1));
        if (count >= k) return i;
    }
    return 1;
}

int main() {
    long long n, k;
    scanf("%lld %lld", &n, &k);
    printf("%lld\n", solve(n, k));
    return 0;
}