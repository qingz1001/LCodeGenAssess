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
    char check_char;
    if (check_digit == 10) {
        check_char = 'X';
    } else {
        check_char = check_digit + '0';
    }

    if (isbn[12] == check_char) {
        printf("Right\n");
    } else {
        isbn[12] = check_char;
        printf("%s\n", isbn);
    }

    return 0;
}