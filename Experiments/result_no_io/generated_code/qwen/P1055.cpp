#include <stdio.h>
#include <string.h>

int main() {
    char isbn[20];
    scanf("%s", isbn);

    int sum = 0;
    for (int i = 0; i < 9; i++) {
        if (isbn[i] == '-') continue;
        sum += (isbn[i] - '0') * (i + 1);
    }

    int check_digit = sum % 11;
    char expected_check_digit = check_digit == 10 ? 'X' : check_digit + '0';

    if (isbn[9] == expected_check_digit) {
        printf("Right\n");
    } else {
        isbn[9] = expected_check_digit;
        printf("%s\n", isbn);
    }

    return 0;
}