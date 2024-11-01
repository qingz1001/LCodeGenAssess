#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DIGITS 6

int primes[] = {2, 3, 5, 7, 11};

void add_numbers(int a[], int b[], int result[]) {
    int carry = 0;
    for (int i = 0; i < MAX_DIGITS; i++) {
        result[i] = a[i] + b[i] + carry;
        if (i < MAX_DIGITS - 1) {
            carry = result[i] / primes[i];
            result[i] %= primes[i];
        }
    }
}

void parse_number(char *str, int num[]) {
    int len = strlen(str);
    int j = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (str[i] == ',') continue;
        num[j++] = str[i] - '0';
    }
    while (j < MAX_DIGITS) {
        num[j++] = 0;
    }
}

int main() {
    char s[100];
    scanf("%s", s);

    char *plus = strchr(s, '+');
    *plus = '\0';
    char *first = s;
    char *second = plus + 1;

    int a[MAX_DIGITS] = {0}, b[MAX_DIGITS] = {0}, result[MAX_DIGITS] = {0};

    parse_number(first, a);
    parse_number(second, b);

    add_numbers(a, b, result);

    int start = MAX_DIGITS - 1;
    while (start > 0 && result[start] == 0) start--;

    for (int i = start; i >= 0; i--) {
        printf("%d", result[i]);
        if (i > 0) printf(",");
    }
    printf("\n");

    return 0;
}