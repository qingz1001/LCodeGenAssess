#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 200

void add(int a[], int b[], int c[]) {
    int carry = 0;
    for (int i = 0; i < MAX_DIGITS; i++) {
        c[i] = a[i] + b[i] + carry;
        carry = c[i] / 10;
        c[i] %= 10;
    }
}

void multiply(int a[], int b) {
    int carry = 0;
    for (int i = 0; i < MAX_DIGITS; i++) {
        a[i] = a[i] * b + carry;
        carry = a[i] / 10;
        a[i] %= 10;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int sum[MAX_DIGITS] = {0};
    int factorial[MAX_DIGITS] = {1};

    for (int i = 1; i <= n; i++) {
        multiply(factorial, i);
        add(sum, factorial, sum);
    }

    int start = MAX_DIGITS - 1;
    while (start > 0 && sum[start] == 0) {
        start--;
    }

    for (int i = start; i >= 0; i--) {
        printf("%d", sum[i]);
    }
    printf("\n");

    return 0;
}