#include <stdio.h>
#include <stdlib.h>

#define MAXN 55
#define MAXFAC 650

void multiply(int *result, int *length, int factor) {
    int carry = 0;
    for (int i = 0; i < *length; ++i) {
        int product = result[i] * factor + carry;
        result[i] = product % 10;
        carry = product / 10;
    }
    while (carry > 0) {
        result[*length] = carry % 10;
        carry /= 10;
        (*length)++;
    }
}

void add(int *a, int *b, int a_length, int b_length) {
    int max_length = a_length > b_length ? a_length : b_length;
    int carry = 0;
    for (int i = 0; i < max_length || carry > 0; ++i) {
        int sum = (i < a_length ? a[i] : 0) + (i < b_length ? b[i] : 0) + carry;
        a[i] = sum % 10;
        carry = sum / 10;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int factorial[MAXN][MAXFAC];
    int factorial_lengths[MAXN];

    // Initialize the first factorial to 1
    factorial[0][0] = 1;
    factorial_lengths[0] = 1;

    long long sum[MAXN];
    sum[0] = 1;

    for (int i = 2; i <= n; ++i) {
        multiply(factorial[i - 1], &factorial_lengths[i - 1], i);
        add(sum, factorial[i - 1], factorial_lengths[i - 1], 1);
    }

    for (int i = factorial_lengths[n] - 1; i >= 0; --i) {
        printf("%d", factorial[n][i]);
    }
    printf("\n");

    return 0;
}