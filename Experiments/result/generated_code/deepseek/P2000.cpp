#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 100000

void multiply(int result[], int factor) {
    int carry = 0;
    for (int i = 0; i < MAX_DIGITS; i++) {
        int product = result[i] * factor + carry;
        result[i] = product % 10;
        carry = product / 10;
    }
}

void divide(int result[], int divisor) {
    int remainder = 0;
    for (int i = MAX_DIGITS - 1; i >= 0; i--) {
        int dividend = result[i] + remainder * 10;
        result[i] = dividend / divisor;
        remainder = dividend % divisor;
    }
}

int main() {
    char input[MAX_DIGITS + 1];
    scanf("%s", input);

    int n[MAX_DIGITS] = {0};
    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        n[i] = input[len - 1 - i] - '0';
    }

    int result[MAX_DIGITS] = {0};
    result[0] = 1;

    // Calculate the number of valid combinations for kkksc03
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 5; j++) {
            for (int k = 0; k <= 7; k++) {
                for (int l = 0; l <= 5; l++) {
                    for (int m = 0; m <= 3; m++) {
                        if (i + j + k + l + m == 0) continue;
                        int temp[MAX_DIGITS];
                        memcpy(temp, n, sizeof(n));
                        multiply(temp, i);
                        multiply(temp, j);
                        multiply(temp, k);
                        multiply(temp, l);
                        multiply(temp, m);
                        divide(temp, i + j + k + l + m);
                        for (int p = 0; p < MAX_DIGITS; p++) {
                            result[p] += temp[p];
                        }
                    }
                }
            }
        }
    }

    // Calculate the number of valid combinations for lzn
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 8; j++) {
            for (int k = 0; k <= 10; k++) {
                for (int l = 0; l <= 3; l++) {
                    if (i + j + k + l == 0) continue;
                    int temp[MAX_DIGITS];
                    memcpy(temp, n, sizeof(n));
                    multiply(temp, i);
                    multiply(temp, j);
                    multiply(temp, k);
                    multiply(temp, l);
                    divide(temp, i + j + k + l);
                    for (int p = 0; p < MAX_DIGITS; p++) {
                        result[p] += temp[p];
                    }
                }
            }
        }
    }

    // Print the result
    int start = MAX_DIGITS - 1;
    while (start > 0 && result[start] == 0) start--;
    for (int i = start; i >= 0; i--) {
        printf("%d", result[i]);
    }
    printf("\n");

    return 0;
}