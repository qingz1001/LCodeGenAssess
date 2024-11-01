#include <stdio.h>
#include <limits.h>

#define MAXN 1000000000

int countDivisors(int n) {
    int count = 0;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            if (i * i == n)
                count += 1;
            else
                count += 2;
        }
    }
    return count;
}

int main() {
    int L, U;
    scanf("%d %d", &L, &U);

    int maxDivisors = 0;
    int numberWithMaxDivisors = INT_MAX;

    for (int i = L; i <= U; ++i) {
        int divisors = countDivisors(i);
        if (divisors > maxDivisors || (divisors == maxDivisors && i < numberWithMaxDivisors)) {
            maxDivisors = divisors;
            numberWithMaxDivisors = i;
        }
    }

    printf("Between %d and %d, %d has a maximum of %d divisors.\n", L, U, numberWithMaxDivisors, maxDivisors);
    return 0;
}