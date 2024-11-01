#include <stdio.h>
#include <string.h>
#include <math.h>

int charToDigit(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1; // Invalid character
}

char digitToChar(int d) {
    if (d >= 0 && d <= 9) return d + '0';
    if (d >= 10 && d <= 15) return d - 10 + 'A';
    return '\0'; // Invalid digit
}

long long convertToDecimal(char *num, int base) {
    long long decimal = 0;
    int len = strlen(num);
    for (int i = 0; i < len; i++) {
        decimal = decimal * base + charToDigit(num[i]);
    }
    return decimal;
}

void convertFromDecimal(long long num, int base, char *result) {
    int index = 0;
    while (num > 0) {
        result[index++] = digitToChar(num % base);
        num /= base;
    }
    result[index] = '\0';
    // Reverse the string
    int len = strlen(result);
    for (int i = 0; i < len / 2; i++) {
        char temp = result[i];
        result[i] = result[len - i - 1];
        result[len - i - 1] = temp;
    }
}

int main() {
    int n, m;
    char num[100];
    char result[100];

    scanf("%d", &n);
    scanf("%s", num);
    scanf("%d", &m);

    long long decimal = convertToDecimal(num, n);
    convertFromDecimal(decimal, m, result);

    printf("%s\n", result);

    return 0;
}