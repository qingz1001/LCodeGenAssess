#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 200

void multiply(int result[], int n) {
    int carry = 0;
    for (int i = 0; i < MAX_DIGITS; i++) {
        int product = result[i] * n + carry;
        result[i] = product % 10;
        carry = product / 10;
    }
}

void add(int result[], int factorial[]) {
    int carry = 0;
    for (int i = 0; i < MAX_DIGITS; i++) {
        int sum = result[i] + factorial[i] + carry;
        result[i] = sum % 10;
        carry = sum / 10;
    }
}

void printResult(int result[]) {
    int i = MAX_DIGITS - 1;
    while (i > 0 && result[i] == 0) i--;
    for (; i >= 0; i--) {
        printf("%d", result[i]);
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);

    int result[MAX_DIGITS] = {0};
    int factorial[MAX_DIGITS] = {1};

    for (int i = 1; i <= n; i++) {
        multiply(factorial, i);
        add(result, factorial);
    }

    printResult(result);

    return 0;
}