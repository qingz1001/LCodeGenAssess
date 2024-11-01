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
    int n, factorial[MAX_DIGITS] = {1}, sum[MAX_DIGITS] = {0}, temp[MAX_DIGITS] = {0};
    
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        multiply(factorial, i);
        memcpy(temp, factorial, sizeof(temp));
        add(sum, temp, sum);
    }
    
    int leading_zero = 1;
    for (int i = MAX_DIGITS - 1; i >= 0; i--) {
        if (sum[i] != 0 || !leading_zero) {
            printf("%d", sum[i]);
            leading_zero = 0;
        }
    }
    if (leading_zero) printf("0");
    printf("\n");
    
    return 0;
}