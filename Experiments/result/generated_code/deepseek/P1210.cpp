#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 20000

int is_palindrome(char *s, int start, int end) {
    while (start < end) {
        if (tolower(s[start]) != tolower(s[end])) {
            return 0;
        }
        start++;
        end--;
    }
    return 1;
}

int main() {
    char input[MAX_LEN];
    char buffer[MAX_LEN];
    int len = 0;
    int max_len = 0;
    int max_start = 0;
    int max_end = 0;

    // Read input
    while (fgets(buffer, MAX_LEN, stdin)) {
        strcat(input, buffer);
    }

    len = strlen(input);

    // Find the longest palindrome
    for (int i = 0; i < len; i++) {
        if (!isalpha(input[i])) continue;
        for (int j = i; j < len; j++) {
            if (!isalpha(input[j])) continue;
            if (is_palindrome(input, i, j)) {
                int pal_len = j - i + 1;
                if (pal_len > max_len) {
                    max_len = pal_len;
                    max_start = i;
                    max_end = j;
                }
            }
        }
    }

    // Output the result
    printf("%d\n", max_len);
    for (int k = max_start; k <= max_end; k++) {
        printf("%c", input[k]);
    }
    printf("\n");

    return 0;
}