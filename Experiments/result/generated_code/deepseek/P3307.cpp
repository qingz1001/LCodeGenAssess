#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MOD 1000000007

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

bool isValid(long long a, long long b, long long c) {
    return gcd(gcd(a, b), c) == 1;
}

long long countValidBeads(long long a) {
    long long count = 0;
    for (long long i = 1; i <= a; i++) {
        for (long long j = i; j <= a; j++) {
            for (long long k = j; k <= a; k++) {
                if (isValid(i, j, k)) {
                    count++;
                }
            }
        }
    }
    return count;
}

long long modPow(long long base, long long exp, long long mod) {
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

long long solve(long long n, long long a) {
    long long validBeads = countValidBeads(a);
    long long result = modPow(validBeads, n, MOD);
    return result;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long n, a;
        scanf("%lld %lld", &n, &a);
        printf("%lld\n", solve(n, a));
    }
    return 0;
}