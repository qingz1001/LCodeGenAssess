#include <stdio.h>
#include <stdlib.h>

int count_divisors(int n) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int L, U;
    scanf("%d %d", &L, &U);

    int max_divisors = 0;
    int number_with_max_divisors = L;

    for (int i = L; i <= U; i++) {
        int divisors = count_divisors(i);
        if (divisors > max_divisors) {
            max_divisors = divisors;
            number_with_max_divisors = i;
        }
    }

    printf("Between %d and %d, %d has a maximum of %d divisors.\n", L, U, number_with_max_divisors, max_divisors);

    return 0;
}