#include <stdio.h>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int num1, den1, num2, den2;
    scanf("%d/%d", &num1, &den1);
    scanf("%d/%d", &num2, &den2);

    // Calculate the product of the two fractions
    int product_num = num1 * num2;
    int product_den = den1 * den2;

    // Reduce the product fraction to its simplest form
    int divisor = gcd(product_num, product_den);
    product_num /= divisor;
    product_den /= divisor;

    // Determine the position in the Cantor table
    int row = 1, col = 1;
    if (product_den == 1) {
        // If the denominator is 1, the position is (product_num, 1)
        col = product_num;
    } else if (product_num == 1) {
        // If the numerator is 1, the position is (1, product_den)
        row = product_den;
    } else {
        // Otherwise, find the position by iterating through the table
        for (int i = 1; i <= product_den; i++) {
            for (int j = 1; j <= i; j++) {
                if (j == product_den && i == product_num) {
                    col = j;
                    row = i;
                    break;
                }
            }
        }
    }

    printf("%d %d\n", col, row);
    return 0;
}