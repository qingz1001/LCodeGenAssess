#include <stdio.h>
#include <string.h>

int isPalindrome(char *s, int left, int right) {
    while (left < right) {
        if (s[left] != s[right]) {
            return 0;
        }
        left++;
        right--;
    }
    return 1;
}

int longestPalindrome(char *s) {
    int n = strlen(s);
    int maxLength = 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (isPalindrome(s, i, j)) {
                int length = j - i + 1;
                if (length > maxLength) {
                    maxLength = length;
                }
            }
        }
    }
    
    return maxLength;
}

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        char s[10000001];
        scanf("%s", s);
        int result = longestPalindrome(s);
        printf("%d\n", result);
    }
    
    return 0;
}