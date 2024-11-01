#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 32

bool isPalindrome(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

void toBase(int num, int base, char *result) {
    int index = 0;
    while (num > 0) {
        int digit = num % base;
        result[index++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
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

bool isDualPalindrome(int num) {
    int count = 0;
    char str[MAX_LEN];
    
    for (int base = 2; base <= 10; base++) {
        toBase(num, base, str);
        if (isPalindrome(str)) {
            count++;
            if (count >= 2) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int n, s;
    scanf("%d %d", &n, &s);
    
    int count = 0;
    int num = s + 1;
    
    while (count < n) {
        if (isDualPalindrome(num)) {
            printf("%d\n", num);
            count++;
        }
        num++;
    }
    
    return 0;
}