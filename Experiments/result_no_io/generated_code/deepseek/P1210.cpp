#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 20000

int is_palindrome(char *s, int start, int end) {
    while (start < end) {
        if (s[start] != s[end]) return 0;
        start++;
        end--;
    }
    return 1;
}

int main() {
    char input[MAX_LEN];
    char buffer[81];
    int len = 0;

    while (fgets(buffer, sizeof(buffer), stdin)) {
        strcpy(input + len, buffer);
        len += strlen(buffer);
    }

    char filtered[MAX_LEN];
    int filtered_len = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(input[i])) {
            filtered[filtered_len++] = tolower(input[i]);
        }
    }
    filtered[filtered_len] = '\0';

    int max_len = 0;
    int max_start = 0;

    for (int i = 0; i < filtered_len; i++) {
        for (int j = i; j < filtered_len; j++) {
            if (is_palindrome(filtered, i, j)) {
                int pal_len = j - i + 1;
                if (pal_len > max_len) {
                    max_len = pal_len;
                    max_start = i;
                }
            }
        }
    }

    printf("%d\n", max_len);
    int output_len = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(input[i])) {
            if (output_len >= max_start && output_len < max_start + max_len) {
                printf("%c", input[i]);
            }
            output_len++;
        } else {
            if (output_len >= max_start && output_len < max_start + max_len) {
                printf("%c", input[i]);
            }
        }
    }
    printf("\n");

    return 0;
}