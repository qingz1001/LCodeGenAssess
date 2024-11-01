#include <stdio.h>
#include <string.h>

int isPalindrome(char *s) {
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++) {
        if (s[i] != s[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

void convertToBase(int num, int base, char *result) {
    int index = 0;
    while (num > 0) {
        int remainder = num % base;
        result[index++] = (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'A');
        num /= base;
    }
    result[index] = '\0';
    strrev(result);
}

int main() {
    int n, s;
    scanf("%d %d", &n, &s);

    int count = 0;
    for (int i = s + 1; count < n; i++) {
        int found = 0;
        char result[33];
        for (int base = 2; base <= 10; base++) {
            convertToBase(i, base, result);
            if (isPalindrome(result)) {
                found++;
                if (found >= 2) {
                    printf("%d\n", i);
                    count++;
                    break;
                }
            }
        }
    }

    return 0;
}