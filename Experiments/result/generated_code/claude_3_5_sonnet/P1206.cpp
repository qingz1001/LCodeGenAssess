#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DIGITS 32

char digits[] = "0123456789ABCDEFGHIJ";

void toBaseB(int num, int base, char *result) {
    int i = 0;
    while (num > 0) {
        result[i++] = digits[num % base];
        num /= base;
    }
    result[i] = '\0';
    
    // Reverse the string
    for (int j = 0; j < i / 2; j++) {
        char temp = result[j];
        result[j] = result[i - j - 1];
        result[i - j - 1] = temp;
    }
}

bool isPalindrome(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int B;
    scanf("%d", &B);
    
    for (int i = 1; i <= 300; i++) {
        int square = i * i;
        char num[MAX_DIGITS], sqr[MAX_DIGITS];
        
        toBaseB(i, B, num);
        toBaseB(square, B, sqr);
        
        if (isPalindrome(sqr)) {
            printf("%s %s\n", num, sqr);
        }
    }
    
    return 0;
}