#include <stdio.h>

int main() {
    int a, product = 37 * a;
    int digit, prev_digit = -1;

    // Read the input
    scanf("%d", &a);

    // Calculate 37 * a
    product = 37 * a;

    // Check if all digits are the same
    while (product > 0) {
        digit = product % 10;
        if (prev_digit != -1 && prev_digit != digit) {
            printf("No\n");
            return 0;
        }
        prev_digit = digit;
        product /= 10;
    }

    printf("Yes\n");
    return 0;
}