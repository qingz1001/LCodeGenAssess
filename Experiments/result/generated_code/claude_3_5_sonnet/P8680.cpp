#include <stdio.h>

int containsSpecialDigits(int num) {
    while (num > 0) {
        int digit = num % 10;
        if (digit == 2 || digit == 0 || digit == 1 || digit == 9) {
            return 1;
        }
        num /= 10;
    }
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);

    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        if (containsSpecialDigits(i)) {
            sum += i;
        }
    }

    printf("%lld\n", sum);

    return 0;
}