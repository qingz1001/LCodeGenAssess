#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 100

int is_palindrome(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

void reverse(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void add(char *a, char *b, char *result, int base) {
    int carry = 0;
    int len_a = strlen(a);
    int len_b = strlen(b);
    int max_len = len_a > len_b ? len_a : len_b;
    int len_result = max_len + 1;
    result[len_result] = '\0';
    for (int i = 0; i < len_result; i++) {
        result[len_result - 1 - i] = '0';
    }
    for (int i = 0; i < max_len; i++) {
        int digit_a = i < len_a ? a[len_a - 1 - i] - '0' : 0;
        int digit_b = i < len_b ? b[len_b - 1 - i] - '0' : 0;
        int sum = digit_a + digit_b + carry;
        result[len_result - 1 - i] = sum % base + '0';
        carry = sum / base;
    }
    if (carry > 0) {
        result[0] = carry + '0';
    }
}

int main() {
    int N;
    char M[MAX_DIGITS + 1];
    scanf("%d", &N);
    scanf("%s", M);

    int step = 0;
    while (step < 30) {
        if (is_palindrome(M)) {
            printf("STEP=%d\n", step);
            return 0;
        }
        char reversed[MAX_DIGITS + 1];
        strcpy(reversed, M);
        reverse(reversed);
        char sum[MAX_DIGITS * 2 + 1];
        add(M, reversed, sum, N);
        strcpy(M, sum);
        step++;
    }
    printf("Impossible!\n");
    return 0;
}