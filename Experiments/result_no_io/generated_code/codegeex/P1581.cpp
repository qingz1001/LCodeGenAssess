#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 100000

int main() {
    char s[MAX_DIGITS];
    scanf("%s", s);

    int len = strlen(s);
    int a[MAX_DIGITS] = {0}, b[MAX_DIGITS] = {0};
    int carry[MAX_DIGITS] = {0};
    int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    int max_prime_index = sizeof(prime) / sizeof(prime[0]);

    int i, j, k;
    for (i = 0; i < len; i++) {
        if (s[i] == ',') {
            continue;
        }
        if (s[i] == '+' || s[i] == '-') {
            k = 0;
        } else {
            a[k] = s[i] - '0';
            k++;
        }
    }

    k = 0;
    for (i = len - 1; i >= 0; i--) {
        if (s[i] == ',') {
            continue;
        }
        if (s[i] == '+' || s[i] == '-') {
            k = 0;
        } else {
            b[k] = s[i] - '0';
            k++;
        }
    }

    int result[MAX_DIGITS] = {0};
    for (i = 0; i < MAX_DIGITS; i++) {
        result[i] = a[i] + b[i] + carry[i];
        carry[i + 1] = result[i] / prime[i % max_prime_index];
        result[i] %= prime[i % max_prime_index];
    }

    int result_len = 0;
    for (i = MAX_DIGITS - 1; i >= 0; i--) {
        if (result[i] != 0) {
            result_len = i + 1;
            break;
        }
    }

    for (i = result_len - 1; i >= 0; i--) {
        printf("%d", result[i]);
        if (i != 0 && i % prime[i % max_prime_index] == 0) {
            printf(",");
        }
    }

    return 0;
}