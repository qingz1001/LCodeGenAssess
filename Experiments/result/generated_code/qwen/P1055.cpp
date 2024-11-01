#include <stdio.h>
#include <string.h>

int main() {
    char isbn[20];
    scanf("%s", isbn);

    int sum = 0;
    for (int i = 0; i < 9; i++) {
        if (isbn[i] >= '0' && isbn[i] <= '9') {
            sum += (isbn[i] - '0') * (i + 1);
        }
    }

    int check_digit = sum % 11;
    char correct_check_digit;
    if (check_digit == 0) {
        correct_check_digit = '0';
    } else if (check_digit == 1) {
        correct_check_digit = 'X';
    } else {
        correct_check_digit = '0' + (11 - check_digit);
    }

    if (correct_check_digit == isbn[12]) {
        printf("Right\n");
    } else {
        printf("%s-%c\n", isbn, correct_check_digit);
    }

    return 0;
}