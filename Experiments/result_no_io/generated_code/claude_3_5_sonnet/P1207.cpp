#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DIGITS 32

bool isPalindrome(int num, int base) {
    char digits[MAX_DIGITS];
    int len = 0;
    
    while (num > 0) {
        digits[len++] = num % base;
        num /= base;
    }
    
    for (int i = 0; i < len / 2; i++) {
        if (digits[i] != digits[len - 1 - i]) {
            return false;
        }
    }
    
    return true;
}

int main() {
    int n, s;
    scanf("%d %d", &n, &s);
    
    int count = 0;
    int num = s + 1;
    
    while (count < n) {
        int palindromeCount = 0;
        
        for (int base = 2; base <= 10; base++) {
            if (isPalindrome(num, base)) {
                palindromeCount++;
                if (palindromeCount >= 2) {
                    printf("%d\n", num);
                    count++;
                    break;
                }
            }
        }
        
        num++;
    }
    
    return 0;
}