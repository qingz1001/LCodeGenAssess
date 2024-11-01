#include <stdio.h>
#include <math.h>

int countDivisors(int n) {
    int count = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int exponent = 0;
            while (n % i == 0) {
                n /= i;
                exponent++;
            }
            count *= (exponent + 1);
        }
    }
    if (n > 1) {
        count *= 2;
    }
    return count;
}

int main() {
    int N;
    scanf("%d", &N);

    int maxDivisors = 0;
    int result = 0;

    for (int i = 1; i <= N; i++) {
        int divisors = countDivisors(i);
        if (divisors > maxDivisors) {
            maxDivisors = divisors;
            result = i;
        }
    }

    printf("%d\n", result);
    return 0;
}