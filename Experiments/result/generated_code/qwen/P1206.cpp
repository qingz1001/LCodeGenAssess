#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return false;
        }
    }
    return true;
}

void convertToBase(int num, int base, char *result) {
    int index = 0;
    do {
        int remainder = num % base;
        result[index++] = (remainder < 10) ? '0' + remainder : 'A' + remainder - 10;
        num /= base;
    } while (num > 0);
    result[index] = '\0';
    for (int i = 0, j = index - 1; i < j; i++, j--) {
        char temp = result[i];
        result[i] = result[j];
        result[j] = temp;
    }
}

int main() {
    int B;
    scanf("%d", &B);

    for (int i = 1; i <= 300; i++) {
        int square = i * i;
        char squareStr[20];
        convertToBase(square, B, squareStr);
        if (isPalindrome(squareStr)) {
            printf("%d %s\n", i, squareStr);
        }
    }

    return 0;
}