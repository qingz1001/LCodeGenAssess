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

long long find_min_n(long long m, long long K) {
    if (K % m == 0) {
        return K / m;
    }
    long long l = lcm(m, K);
    return l / m;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long m, K;
        scanf("%lld %lld", &m, &K);
        printf("%lld\n", find_min_n(m, K));
    }
    return 0;
}