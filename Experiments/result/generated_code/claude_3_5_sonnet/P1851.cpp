#include <stdio.h>

int sum_of_divisors(int n) {
    int sum = 0;
    for (int i = 1; i < n; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int s;
    scanf("%d", &s);

    for (int a = s; a <= 18000; a++) {
        int b = sum_of_divisors(a);
        if (b > a && sum_of_divisors(b) == a) {
            printf("%d %d\n", a, b);
            return 0;
        }
    }

    return 0;
}