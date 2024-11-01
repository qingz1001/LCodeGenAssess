#include <stdio.h>

int sum_of_divisors(int n) {
    int sum = 0;
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int s;
    scanf("%d", &s);

    for (int a = s; ; a++) {
        int sum_a = sum_of_divisors(a);
        if (sum_a < s) continue;

        int b = sum_a;
        int sum_b = sum_of_divisors(b);

        if (sum_b == a && a != b) {
            printf("%d %d\n", a, b);
            break;
        }
    }

    return 0;
}