#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int expandAroundCenter(char *s, int left, int right) {
    while (left >= 0 && right < strlen(s) && s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1;
}

void longestPalindromeSubstrings(char **strs, int n) {
    for (int i = 0; i < n; i++) {
        char *s = strs[i];
        int len = strlen(s);
        int start = 0, end = 0;

        for (int j = 0; j < len; j++) {
            int len1 = expandAroundCenter(s, j, j); // Odd length palindrome
            int len2 = expandAroundCenter(s, j, j + 1); // Even length palindrome
            int maxLen = max(len1, len2);

            if (maxLen > end - start) {
                start = j - (maxLen - 1) / 2;
                end = j + maxLen / 2;
            }
        }

        printf("%d\n", end - start + 1);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    char *strs[n];

    for (int i = 0; i < n; i++) {
        strs[i] = (char *)malloc(10000001 * sizeof(char));
        scanf("%s", strs[i]);
    }

    longestPalindromeSubstrings(strs, n);

    for (int i = 0; i < n; i++) {
        free(strs[i]);
    }

    return 0;
}