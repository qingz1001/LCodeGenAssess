#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(int num) {
    int originalNum = num;
    int reversedNum = 0;
    while (num > 0) {
        reversedNum = reversedNum * 10 + num % 10;
        num /= 10;
    }
    return originalNum == reversedNum;
}

bool isDualPalindrome(int num) {
    int count = 0;
    for (int base = 2; base <= 10; base++) {
        if (isPalindrome(num)) {
            count++;
        }
        num = (num - 1) / base + 1;
    }
    return count >= 2;
}

int main() {
    int n, s;
    scanf("%d %d", &n, &s);

    for (int i = s + 1; i < s + n + 1; i++) {
        if (isDualPalindrome(i)) {
            printf("%d\n", i);
        }
    }

    return 0;
}