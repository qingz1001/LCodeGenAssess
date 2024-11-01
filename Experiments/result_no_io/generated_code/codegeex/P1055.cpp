#include <stdio.h>
#include <string.h>

int main() {
    char isbn[14];
    int sum = 0;
    scanf("%s", isbn);

    for (int i = 0; i < 12; i++) {
        if (isbn[i] == '-') continue;
        sum += (isbn[i] - '0') * (i % 10 + 1);
    }

    char check = sum % 11 == 10 ? 'X' : sum % 11 + '0';
    if (check == isbn[12]) {
        printf("Right\n");
    } else {
        isbn[12] = check;
        printf("%s\n", isbn);
    }

    return 0;
}