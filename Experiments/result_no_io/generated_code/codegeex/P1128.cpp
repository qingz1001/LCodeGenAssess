#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 50000

int prime[MAX_N + 1];
int min_factor[MAX_N + 1];
int min_exponent[MAX_N + 1];
int num_primes;

void sieve() {
    int i, j;
    for (i = 2; i <= MAX_N; i++) {
        if (min_factor[i] == 0) {
            prime[num_primes++] = i;
            min_factor[i] = i;
        }
        for (j = 0; j < num_primes && prime[j] * i <= MAX_N; j++) {
            min_factor[prime[j] * i] = prime[j];
            if (i % prime[j] == 0) break;
        }
    }
}

void factorize(int n) {
    int i;
    for (i = 0; i < num_primes && prime[i] * prime[i] <= n; i++) {
        if (n % prime[i] == 0) {
            int exponent = 0;
            while (n % prime[i] == 0) {
                n /= prime[i];
                exponent++;
            }
            if (exponent > min_exponent[prime[i]]) {
                min_exponent[prime[i]] = exponent;
            }
        }
    }
    if (n > 1) {
        if (min_exponent[n] == 0) {
            min_exponent[n] = 1;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    sieve();
    factorize(n);

    unsigned long long result = 1;
    for (int i = 2; i <= MAX_N; i++) {
        for (int j = 0; j < min_exponent[i]; j++) {
            result *= i;
        }
    }

    printf("%llu\n", result);
    return 0;
}