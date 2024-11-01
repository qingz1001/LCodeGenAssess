#include <stdio.h>

int sum_of_divisors(int n) {
    int sum = 1; // Start with 1 because it is a divisor of all numbers
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    return sum;
}

int main() {
    int s;
    scanf("%d", &s);

    while (1) {
        int a = s++;
        int b = sum_of_divisors(a);
        if (sum_of_divisors(b) == a && a != b) {
            printf("%d %d\n", a, b);
            break;
        }
    }

    return 0;
}