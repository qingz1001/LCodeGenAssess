#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000000
#define MAX_M 1000000000
#define MAX_K 2000

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    long long N, M, K;
    scanf("%lld %lld %lld", &N, &M, &K);

    long long count = 0;

    for (long long x = 1; x <= N; ++x) {
        for (long long y = 1; y <= M; ++y) {
            if (gcd(x, y) == 1) {
                long long num = x * K;
                long long den = y;
                while (num % den != 0 && den % K == 0) {
                    den /= K;
                }
                if (den % K == 0) {
                    count++;
                }
            }
        }
    }

    printf("%lld\n", count);

    return 0;
}