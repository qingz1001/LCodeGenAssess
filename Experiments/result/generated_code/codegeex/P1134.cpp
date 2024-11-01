#include <stdio.h>

int main() {
    int n, rightmost_non_zero = 1;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        rightmost_non_zero *= i;
        while (rightmost_non_zero % 10 == 0) {
            rightmost_non_zero /= 10;
        }
        rightmost_non_zero %= 100000; // Keep only the last 5 digits
    }

    printf("%d\n", rightmost_non_zero % 10);
    return 0;
}