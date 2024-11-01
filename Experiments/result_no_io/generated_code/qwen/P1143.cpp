#include <stdio.h>
#include <string.h>

int convertToDecimal(char *num, int base) {
    int len = strlen(num);
    int decimal = 0;
    for (int i = 0; i < len; i++) {
        int digit;
        if (num[i] >= '0' && num[i] <= '9') {
            digit = num[i] - '0';
        } else {
            digit = num[i] - 'A' + 10;
        }
        decimal = decimal * base + digit;
    }
    return decimal;
}

void convertFromDecimal(int num, int base, char *result) {
    int index = 0;
    while (num > 0) {
        int remainder = num % base;
        if (remainder < 10) {
            result[index++] = remainder + '0';
        } else {
            result[index++] = remainder - 10 + 'A';
        }
        num /= base;
    }
    result[index] = '\0';
    strrev(result);
}

int main() {
    int n, m;
    scanf("%d", &n);
    char num[20];
    scanf("%s", num);
    scanf("%d", &m);

    int decimal = convertToDecimal(num, n);
    char result[20];
    convertFromDecimal(decimal, m, result);

    printf("%s\n", result);

    return 0;
}