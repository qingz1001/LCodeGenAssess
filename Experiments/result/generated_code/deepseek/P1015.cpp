#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_DIGITS 101

bool is_palindrome(char num[], int len) {
    for (int i = 0; i < len / 2; i++) {
        if (num[i] != num[len - 1 - i]) {
            return false;
        }
    }
    return true;
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
    int len = strlen(num1);
    reverse_string(num1, len);
    reverse_string(num2, len);

    for (int i = 0; i < len; i++) {
        int digit1 = (num1[i] >= '0' && num1[i] <= '9') ? num1[i] - '0' : num1[i] - 'A' + 10;
        int digit2 = (num2[i] >= '0' && num2[i] <= '9') ? num2[i] - '0' : num2[i] - 'A' + 10;
        int sum = digit1 + digit2 + carry;
        result[i] = (sum % base < 10) ? sum % base + '0' : sum % base - 10 + 'A';
        carry = sum / base;
    }

    if (carry > 0) {
        result[len] = (carry < 10) ? carry + '0' : carry - 10 + 'A';
        result[len + 1] = '\0';
    } else {
        result[len] = '\0';
    }

    reverse_string(result, strlen(result));
}

int main() {
    int N;
    char M[MAX_DIGITS];
    scanf("%d", &N);
    scanf("%s", M);

    int steps = 0;
    char reversed[MAX_DIGITS];
    char sum[MAX_DIGITS];

    while (steps <= 30) {
        int len = strlen(M);
        strcpy(reversed, M);
        reverse_string(reversed, len);

        if (is_palindrome(M, len)) {
            printf("STEP=%d\n", steps);
            return 0;
        }

        add_in_base(M, reversed, N, sum);
        strcpy(M, sum);
        steps++;
    }

    printf("Impossible!\n");
    return 0;
}