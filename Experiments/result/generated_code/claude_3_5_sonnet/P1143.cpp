#include <stdio.h>
#include <string.h>
#include <ctype.h>

long long convert_to_decimal(char *num, int base) {
    long long decimal = 0;
    int len = strlen(num);
    for (int i = 0; i < len; i++) {
        int digit;
        if (isdigit(num[i])) {
            digit = num[i] - '0';
        } else {
            digit = toupper(num[i]) - 'A' + 10;
        }
        decimal = decimal * base + digit;
    }
    return decimal;
}

void convert_from_decimal(long long decimal, int base) {
    char result[100];
    int index = 0;

    if (decimal == 0) {
        printf("0");
        return;
    }

    while (decimal > 0) {
        int remainder = decimal % base;
        if (remainder < 10) {
            result[index++] = remainder + '0';
        } else {
            result[index++] = remainder - 10 + 'A';
        }
        decimal /= base;
    }

    for (int i = index - 1; i >= 0; i--) {
        printf("%c", result[i]);
    }
}

int main() {
    int n, m;
    char num[100];

    scanf("%d", &n);
    scanf("%s", num);
    scanf("%d", &m);

    long long decimal = convert_to_decimal(num, n);
    convert_from_decimal(decimal, m);

    return 0;
}