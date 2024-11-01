#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MOD 1000000007

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long mod_pow(long long base, long long exp, long long mod) {
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
    long long valid_beads = 0;
    for (long long x1 = 1; x1 <= a; x1++) {
        for (long long x2 = 1; x2 <= a; x2++) {
            for (long long x3 = 1; x3 <= a; x3++) {
                if (gcd(gcd(x1, x2), x3) == 1) {
                    valid_beads++;
                }
            }
        }
    }

    long long total_beads = mod_pow(valid_beads, n, MOD);
    return total_beads;
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