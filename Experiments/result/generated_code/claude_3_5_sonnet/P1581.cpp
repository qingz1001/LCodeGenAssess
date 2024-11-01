#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DIGITS 5
#define MAX_PRIMES 5

int primes[MAX_PRIMES] = {2, 3, 5, 7, 11};

void add_numbers(int a[], int b[], int result[], int len) {
    int carry = 0;
    for (int i = 0; i < len; i++) {
        int sum = a[i] + b[i] + carry;
        result[i] = sum % primes[i];
        carry = sum / primes[i];
    }
    if (carry > 0) {
        result[len] = carry;
    }
}

int main() {
    char input[100];
    fgets(input, sizeof(input), stdin);

    int a[MAX_DIGITS] = {0}, b[MAX_DIGITS] = {0}, result[MAX_DIGITS + 1] = {0};
    int len_a = 0, len_b = 0;

    char *token = strtok(input, "+");
    char *num_a = token;
    token = strtok(NULL, "\n");
    char *num_b = token;

    for (int i = strlen(num_a) - 1; i >= 0; i--) {
        if (num_a[i] >= '0' && num_a[i] <= '9') {
            a[len_a++] = num_a[i] - '0';
        }
    }

    for (int i = strlen(num_b) - 1; i >= 0; i--) {
        if (num_b[i] >= '0' && num_b[i] <= '9') {
            b[len_b++] = num_b[i] - '0';
        }
    }

    int max_len = (len_a > len_b) ? len_a : len_b;
    add_numbers(a, b, result, max_len);

    int result_len = max_len;
    if (result[max_len] > 0) {
        result_len++;
    }

    for (int i = result_len - 1; i >= 0; i--) {
        printf("%d", result[i]);
        if (i > 0) {
            printf(",");
        }
    }
    printf("\n");

    return 0;
}