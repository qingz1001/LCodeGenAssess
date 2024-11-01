#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 101

char num[MAX_LEN];
int base;

int char_to_int(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    return c - 'A' + 10;
}

char int_to_char(int n) {
    if (n < 10) return n + '0';
    return n - 10 + 'A';
}

void reverse_str(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

bool is_palindrome(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) return false;
    }
    return true;
}

void add(char *a, char *b, char *result) {
    int len_a = strlen(a), len_b = strlen(b);
    int carry = 0, i = len_a - 1, j = len_b - 1, k = 0;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += char_to_int(a[i--]);
        if (j >= 0) sum += char_to_int(b[j--]);
        result[k++] = int_to_char(sum % base);
        carry = sum / base;
    }
    result[k] = '\0';
    reverse_str(result);
}

int main() {
    scanf("%d %s", &base, num);

    for (int step = 1; step <= 30; step++) {
        char reversed[MAX_LEN], sum[MAX_LEN];
        strcpy(reversed, num);
        reverse_str(reversed);
        add(num, reversed, sum);

        if (is_palindrome(sum)) {
            printf("STEP=%d\n", step);
            return 0;
        }
        strcpy(num, sum);
    }

    printf("Impossible!\n");
    return 0;
}