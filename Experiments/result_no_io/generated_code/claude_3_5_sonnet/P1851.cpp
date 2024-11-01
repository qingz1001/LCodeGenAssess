#include <stdio.h>

int sumOfDivisors(int n) {
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i * i != n) {
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
        int b = sumOfDivisors(a);
        if (b < a && sumOfDivisors(b) == a) {
            printf("%d %d\n", a, b);
            break;
        }
    }

    return 0;
}