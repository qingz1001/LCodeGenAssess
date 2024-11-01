#include <stdio.h>

// Function to calculate the greatest common divisor (GCD)
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int n;
    scanf("%d", &n);

    // Calculate the numerator and denominator of the fraction
    int numerator = n;
    int denominator = 1;

    // Simplify the fraction
    int divisor = gcd(numerator, denominator);
    numerator /= divisor;
    denominator /= divisor;

    // Calculate the integer part and the remainder
    int integer_part = numerator / denominator;
    numerator %= denominator;

    // Output the result
    if (numerator == 0) {
        // If there is no remainder, output the integer part only
        printf("%d\n", integer_part);
    } else {
        // If there is a remainder, output the fraction
        printf("%d\n", numerator);
        printf("%d\n", integer_part);
        for (int i = 0; i < (int)log10(denominator) + 1; i++) {
            printf("-");
        }
        printf("\n%d\n", denominator);
    }

    return 0;
}