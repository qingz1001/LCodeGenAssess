#include <stdio.h>
#include <math.h>

#define MAX 1000000

int divisors[MAX + 1] = {0};

void sieve() {
    for (int i = 1; i <= MAX; i++) {
        for (int j = i; j <= MAX; j += i) {
            divisors[j]++;
        }
    }
}

int main() {
    int L, U;
    scanf("%d %d", &L, &U);

    sieve();

    int max_divisors = 0;
    int max_number = L;

    for (int i = L; i <= U; i++) {
        if (i <= MAX) {
            if (divisors[i] > max_divisors) {
                max_divisors = divisors[i];
                max_number = i;
            }
        } else {
            int count = 0;
            for (int j = 1; j <= sqrt(i); j++) {
                if (i % j == 0) {
                    if (i / j == j) {
                        count++;
                    } else {
                        count += 2;
                    }
                }
            }
            if (count > max_divisors) {
                max_divisors = count;
                max_number = i;
            }
        }
    }

    printf("Between %d and %d, %d has a maximum of %d divisors.\n", L, U, max_number, max_divisors);

    return 0;
}