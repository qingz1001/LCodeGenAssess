#include <stdio.h>
#include <string.h>

int main() {
    char isbn[14];
    scanf("%s", isbn);

    int sum = 0;
    int factor = 1;
    for (int i = 0; i < 12; i++) {
        if (isbn[i] != '-') {
            sum += (isbn[i] - '0') * factor;
            factor++;
        }
    }

    int check_digit = sum % 11;
    char expected_check_digit = (check_digit == 10) ? 'X' : (check_digit + '0');

    if (isbn[12] == expected_check_digit) {
        printf("Right\n");
    } else {
        isbn[12] = expected_check_digit;
        printf("%s\n", isbn);
    }

    return 0;
}