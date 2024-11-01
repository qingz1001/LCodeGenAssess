#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 500

void multiply(int result[], int n) {
    int carry = 0;
    for (int i = 0; i < MAX_DIGITS; i++) {
        int product = result[i] * n + carry;
        result[i] = product % 10;
        carry = product / 10;
    }
}

void power_of_two(int result[], int p) {
    result[0] = 1;
    for (int i = 0; i < p; i++) {
        multiply(result, 2);
    }
}

int main() {
    int p;
    scanf("%d", &p);

    // Calculate the number of digits
    int digits = (int)(p * 0.30103) + 1; // log10(2) ≈ 0.30103
    printf("%d\n", digits);

    // Calculate the last 500 digits of 2^p - 1
    int result[MAX_DIGITS] = {0};
    power_of_two(result, p);

    // Subtract 1 from the result
    result[0] -= 1;
    for (int i = 0; i < MAX_DIGITS - 1; i++) {
        if (result[i] < 0) {
            result[i] += 10;
            result[i + 1] -= 1;
        }
    }

    // Print the last 500 digits
    for (int i = 499; i >= 0; i--) {
        printf("%d", result[i]);
        if (i % 50 == 0) {
            printf("\n");
        }
    }

    return 0;
}