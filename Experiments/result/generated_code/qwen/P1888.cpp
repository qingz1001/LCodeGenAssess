#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void print_fraction(int numerator, int denominator) {
    int common_divisor = gcd(numerator, denominator);
    printf("%d/%d\n", numerator / common_divisor, denominator / common_divisor);
}

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    // Sort the numbers to ensure a <= b <= c
    if (a > b) { int temp = a; a = b; b = temp; }
    if (a > c) { int temp = a; a = c; c = temp; }
    if (b > c) { int temp = b; b = c; c = temp; }

    // Check if they form a Pythagorean triple
    if (a * a + b * b == c * c) {
        // Calculate the sine of the smaller acute angle
        int sine_numerator = a;
        int sine_denominator = c;

        // Print the fraction in its simplest form
        print_fraction(sine_numerator, sine_denominator);
    } else {
        printf("Invalid input: Not a Pythagorean triple.\n");
    }

    return 0;
}