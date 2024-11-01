#include <stdio.h>
#include <math.h>

#define MAX_N 50000

int main() {
    int n;
    scanf("%d", &n);

    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    int num_primes = sizeof(primes) / sizeof(primes[0]);

    int factor_counts[MAX_N + 1];
    for (int i = 1; i <= MAX_N; i++) {
        factor_counts[i] = 0;
    }

    for (int i = 0; i < num_primes; i++) {
        for (int j = primes[i]; j <= MAX_N; j *= primes[i]) {
            factor_counts[j]++;
        }
    }

    int min_product = 0;
    for (int i = 2; i <= MAX_N; i++) {
        if (factor_counts[i] == n) {
            min_product = i;
            break;
        }
    }

    printf("%d\n", min_product);

    return 0;
}