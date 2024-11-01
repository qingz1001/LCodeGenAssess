#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 20005
#define MAX_LINE_LEN 81

char input[MAX_LEN];
char processed[MAX_LEN];
int len;

void preprocess() {
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(input[i])) {
            processed[j++] = tolower(input[i]);
        }
    }
    processed[j] = '\0';
}

int expandAroundCenter(char *s, int left, int right) {
    while (left >= 0 && right < strlen(s) && s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1;
}

void findLongestPalindrome() {
    int start = 0, end = 0;
    for (int i = 0; i < strlen(processed); i++) {
        int len1 = expandAroundCenter(processed, i, i);
        int len2 = expandAroundCenter(processed, i, i + 1);
        int maxLen = len1 > len2 ? len1 : len2;
        if (maxLen > end - start) {
            start = i - (maxLen - 1) / 2;
            end = i + maxLen / 2;
        }
    }
    printf("%d\n", end - start + 1);
    for (int i = start; i <= end; i++) {
        putchar(processed[i]);
    }
    putchar('\n');
}

int main() {
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    len = strlen(input);
    preprocess();
    findLongestPalindrome();
    return 0;
}