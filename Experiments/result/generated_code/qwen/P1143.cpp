#include <stdio.h>
#include <stdlib.h>

int convertToDecimal(const char *num, int base) {
    int decimal = 0;
    while (*num != '\0') {
        if (*num >= '0' && *num <= '9')
            decimal = decimal * base + (*num - '0');
        else if (*num >= 'A' && *num <= 'F')
            decimal = decimal * base + (*num - 'A' + 10);
        num++;
    }
    return decimal;
}

void convertFromDecimal(int num, int base, char *result) {
    int i = 0;
    do {
        result[i++] = (num % base < 10) ? (num % base + '0') : ('A' + num % base - 10);
    } while (num /= base);
    result[i] = '\0';
    for (int j = 0; j < i / 2; j++) {
        char temp = result[j];
        result[j] = result[i - j - 1];
        result[i - j - 1] = temp;
    }
}

int main() {
    int fromBase, toBase;
    scanf("%d", &fromBase);
    char num[100];
    scanf("%s", num);
    scanf("%d", &toBase);

    int decimal = convertToDecimal(num, fromBase);
    char result[100];
    convertFromDecimal(decimal, toBase, result);

    printf("%s\n", result);

    return 0;
}