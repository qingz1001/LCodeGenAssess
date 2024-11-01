#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000000

int main() {
    int L, U;
    scanf("%d %d", &L, &U);

    int max_divisors = 0;
    int max_number = 0;

    for (int i = L; i <= U; i++) {
        int divisors = 0;
        for (int j = 1; j * j <= i; j++) {
            if (i % j == 0) {
                divisors++;
                if (j * j != i) {
                    divisors++;
                }
            }
        }
        if (divisors > max_divisors) {
            max_divisors = divisors;
            max_number = i;
        }
    }

    printf("Between %d and %d, %d has a maximum of %d divisors.\n", L, U, max_number, max_divisors);

    return 0;
}