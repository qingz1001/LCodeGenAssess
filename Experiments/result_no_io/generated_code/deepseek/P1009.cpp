#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 200

void multiply(int result[], int *result_len, int factor) {
    int carry = 0;
    for (int i = 0; i < *result_len; i++) {
        int product = result[i] * factor + carry;
        result[i] = product % 10;
        carry = product / 10;
    }
    while (carry > 0) {
        result[*result_len] = carry % 10;
        carry /= 10;
        (*result_len)++;
    }
}

void add(int sum[], int *sum_len, int factorial[], int factorial_len) {
    int carry = 0;
    int max_len = (*sum_len > factorial_len) ? *sum_len : factorial_len;
    for (int i = 0; i < max_len; i++) {
        int temp = sum[i] + factorial[i] + carry;
        sum[i] = temp % 10;
        carry = temp / 10;
    }
    if (carry > 0) {
        sum[max_len] = carry;
        (*sum_len) = max_len + 1;
    } else {
        (*sum_len) = max_len;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int sum[MAX_DIGITS] = {0};
    int sum_len = 1;
    int factorial[MAX_DIGITS] = {1};
    int factorial_len = 1;

    for (int i = 1; i <= n; i++) {
        multiply(factorial, &factorial_len, i);
        add(sum, &sum_len, factorial, factorial_len);
    }

    for (int i = sum_len - 1; i >= 0; i--) {
        printf("%d", sum[i]);
    }
    printf("\n");

    return 0;
}