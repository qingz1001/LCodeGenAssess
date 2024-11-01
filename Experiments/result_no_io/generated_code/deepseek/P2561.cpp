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

void factorial(int n, int result[]) {
    memset(result, 0, MAX_DIGITS * sizeof(int));
    result[0] = 1;
    for (int i = 2; i <= n; i++) {
        multiply(result, i);
    }
}

void printResult(int result[]) {
    int i = MAX_DIGITS - 1;
    while (i > 0 && result[i] == 0) {
        i--;
    }
    while (i >= 0) {
        printf("%d", result[i--]);
    }
    printf("\n");
}

int main() {
    int n;
    int result[MAX_DIGITS];
    scanf("%d", &n);
    factorial(n, result);
    printResult(result);
    return 0;
}