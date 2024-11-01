#include <stdio.h>

int sum_of_divisors(int n) {
    int sum = 1;
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

    for (int a = s; ; a++) {
        int sum_a = sum_of_divisors(a);
        for (int b = 1; b < sum_a; b++) {
            if (sum_of_divisors(b) == sum_a && b < sum_a) {
                printf("%d %d\n", a, b);
                return 0;
            }
        }
    }

    return 0;
}