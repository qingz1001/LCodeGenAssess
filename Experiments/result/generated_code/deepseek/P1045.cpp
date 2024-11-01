#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_DIGITS 500

void multiply(int res[], int a[], int b) {
    int carry = 0;
    for (int i = 0; i < MAX_DIGITS; i++) {
        res[i] = a[i] * b + carry;
        carry = res[i] / 10;
        res[i] %= 10;
    }
}

void power(int res[], int base[], int exp) {
    int temp[MAX_DIGITS] = {0};
    memcpy(temp, base, MAX_DIGITS * sizeof(int));

    for (int i = 1; i < exp; i++) {
        multiply(res, temp, 2);
        memcpy(temp, res, MAX_DIGITS * sizeof(int));
    }
}

int main() {
    int P;
    scanf("%d", &P);

    // Calculate the number of digits
    int digits = (int)(P * log10(2)) + 1;
    printf("%d\n", digits);

    // Calculate the last 500 digits of 2^P - 1
    int result[MAX_DIGITS] = {0};
    result[0] = 1;

    power(result, result, P);

    // Subtract 1 from the result
    result[0] -= 1;
    for (int i = 1; i < MAX_DIGITS; i++) {
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