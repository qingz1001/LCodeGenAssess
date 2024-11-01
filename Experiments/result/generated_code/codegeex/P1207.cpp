#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(int num, int base) {
    int digits[32];
    int count = 0;
    
    while (num > 0) {
        digits[count++] = num % base;
        num /= base;
    }
    
    for (int i = 0; i < count / 2; i++) {
        if (digits[i] != digits[count - i - 1]) {
            return false;
        }
    }
    
    return true;
}

bool hasTwoPalindromes(int num) {
    int count = 0;
    for (int base = 2; base <= 10; base++) {
        if (isPalindrome(num, base)) {
            count++;
        }
        if (count >= 2) {
            return true;
        }
    }
    return false;
}

int main() {
    int n, s;
    scanf("%d %d", &n, &s);
    
    int count = 0;
    for (int num = s + 1; count < n; num++) {
        if (hasTwoPalindromes(num)) {
            printf("%d\n", num);
            count++;
        }
    }
    
    return 0;
}