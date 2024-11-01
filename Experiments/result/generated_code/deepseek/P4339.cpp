#include <stdio.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}

long long solve(long long m, long long K) {
    long long L = lcm(m, K);
    return L / K;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long m, K;
        scanf("%lld %lld", &m, &K);
        printf("%lld\n", solve(m, K));
    }
    return 0;
}