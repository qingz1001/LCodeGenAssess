#include <stdio.h>
#include <string.h>

char digit[] = "0123456789ABCDEFGHIJ";

void toBase(int num, int base, char *result) {
    int index = 0;
    while (num > 0) {
        result[index++] = digit[num % base];
        num /= base;
    }
    result[index] = '\0';
    
    // Reverse the string
    for (int i = 0; i < index / 2; i++) {
        char temp = result[i];
        result[i] = result[index - 1 - i];
        result[index - 1 - i] = temp;
    }
}

int isPalindrome(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int B;
    scanf("%d", &B);
    
    char num[20], square[20];
    for (int i = 1; i <= 300; i++) {
        toBase(i, B, num);
        toBase(i * i, B, square);
        if (isPalindrome(square)) {
            printf("%s %s\n", num, square);
        }
    }
    
    return 0;
}