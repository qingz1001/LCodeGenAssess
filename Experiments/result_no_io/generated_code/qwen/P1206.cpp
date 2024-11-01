#include <stdio.h>
#include <string.h>

int isPalindrome(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

void convertToBase(int num, int base, char *result) {
    int index = 0;
    while (num > 0) {
        int remainder = num % base;
        result[index++] = remainder >= 10 ? 'A' + remainder - 10 : '0' + remainder;
        num /= base;
    }
    result[index] = '\0';
    strrev(result);
}

int main() {
    int B;
    scanf("%d", &B);

    for (int i = 1; i <= 300; i++) {
        long long square = (long long)i * i;
        char baseB[50];
        convertToBase(square, B, baseB);
        if (isPalindrome(baseB)) {
            printf("%s %s\n", convertToBase(i, B, baseB), baseB);
        }
    }

    return 0;
}