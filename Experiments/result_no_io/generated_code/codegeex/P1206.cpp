#include <stdio.h>
#include <string.h>

void convertToBase(int num, int base, char* result) {
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i = 0;
    
    while (num > 0) {
        result[i++] = digits[num % base];
        num /= base;
    }
    
    result[i] = '\0';
    strrev(result);
}

int isPalindrome(char* str) {
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
    
    for (int i = 1; i <= 300; i++) {
        int square = i * i;
        char numStr[100], squareStr[100];
        
        convertToBase(i, B, numStr);
        convertToBase(square, B, squareStr);
        
        if (isPalindrome(squareStr)) {
            printf("%s %s\n", numStr, squareStr);
        }
    }
    
    return 0;
}