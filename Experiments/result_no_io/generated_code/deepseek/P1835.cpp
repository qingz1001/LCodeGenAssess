#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX 1000000

bool is_prime[MAX];

void sieve(int limit) {
    for (int i = 0; i <= limit; i++) {
        is_prime[i] = true;
    }
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= limit; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int count_primes_in_range(int L, int R) {
    int count = 0;
    int limit = (int)sqrt(R);
    sieve(limit);

    bool is_prime_range[R - L + 1];
    for (int i = 0; i <= R - L; i++) {
        is_prime_range[i] = true;
    }

    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            int start = (L / i) * i;
            if (start < L) start += i;
            if (start == i) start += i;
            for (int j = start; j <= R; j += i) {
                is_prime_range[j - L] = false;
            }
        }
    }

    for (int i = 0; i <= R - L; i++) {
        if (is_prime_range[i]) {
            count++;
        }
    }

    return count;
}

int main() {
    int L, R;
    scanf("%d %d", &L, &R);
    int result = count_primes_in_range(L, R);
    printf("%d\n", result);
    return 0;
}