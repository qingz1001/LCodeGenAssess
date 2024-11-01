#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 101
#define MAX_STEPS 30

int is_palindrome(char num[], int len) {
    for (int i = 0; i < len / 2; i++) {
        if (num[i] != num[len - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

void reverse_string(char str[], int len) {
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void add_in_base(char num1[], char num2[], int base, char result[]) {
    int carry = 0;
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int max_len = len1 > len2 ? len1 : len2;
    int i = 0;

    for (i = 0; i < max_len; i++) {
        int digit1 = i < len1 ? (num1[i] >= 'A' ? num1[i] - 'A' + 10 : num1[i] - '0') : 0;
        int digit2 = i < len2 ? (num2[i] >= 'A' ? num2[i] - 'A' + 10 : num2[i] - '0') : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / base;
        result[i] = (sum % base) + (sum % base < 10 ? '0' : 'A' - 10);
    }

    if (carry > 0) {
        result[i++] = carry + (carry < 10 ? '0' : 'A' - 10);
    }

    result[i] = '\0';
}

int main() {
    int N;
    char M[MAX_DIGITS];
    scanf("%d %s", &N, M);

    int steps = 0;
    int len = strlen(M);
    char reversed[MAX_DIGITS];
    char sum[MAX_DIGITS];

    while (steps <= MAX_STEPS) {
        if (is_palindrome(M, len)) {
            printf("STEP=%d\n", steps);
            return 0;
        }

        strcpy(reversed, M);
        reverse_string(reversed, len);
        add_in_base(M, reversed, N, sum);
        strcpy(M, sum);
        len = strlen(M);
        steps++;
    }

    printf("Impossible!\n");
    return 0;
}