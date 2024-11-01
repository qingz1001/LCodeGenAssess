#include <stdio.h>
#include <math.h>

// 计算一个数的约数个数
int countDivisors(int n) {
    int count = 0;
    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            count++;
            if (i != n / i) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int L, U;
    scanf("%d %d", &L, &U);

    int maxDivisors = 0;
    int maxNumber = L;

    for (int i = L; i <= U; i++) {
        int divisors = countDivisors(i);
        if (divisors > maxDivisors) {
            maxDivisors = divisors;
            maxNumber = i;
        }
    }

    printf("Between %d and %d, %d has a maximum of %d divisors.\n", L, U, maxNumber, maxDivisors);

    return 0;
}