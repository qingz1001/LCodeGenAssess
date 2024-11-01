#include <stdio.h>
#include <string.h>

int main() {
    char isbn[14];
    scanf("%s", isbn);

    int sum = 0;
    for (int i = 0; i < 12; i++) {
        if (isbn[i] != '-') {
            sum += (isbn[i] - '0') * (i % 10 + 1);
        }
    }

    char check_digit = sum % 11 + '0';
    if (check_digit == '10') {
        check_digit = 'X';
    }

    if (check_digit == isbn[12]) {
        printf("Right\n");
    } else {
        isbn[12] = check_digit;
        printf("%s\n", isbn);
    }

    return 0;
}