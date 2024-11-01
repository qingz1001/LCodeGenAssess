#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 20000

char text[MAX_LEN];
char cleaned[MAX_LEN];
int len, clean_len;

int is_palindrome(int start, int end) {
    while (start < end) {
        if (cleaned[start] != cleaned[end]) return 0;
        start++;
        end--;
    }
    return 1;
}

int main() {
    char c;
    int i = 0, j = 0;
    while ((c = getchar()) != EOF && i < MAX_LEN - 1) {
        text[i++] = c;
        if (isalpha(c)) cleaned[j++] = tolower(c);
    }
    text[i] = '\0';
    len = i;
    clean_len = j;

    int max_len = 0, max_start = 0, max_end = 0;
    for (i = 0; i < clean_len; i++) {
        for (j = clean_len - 1; j > i; j--) {
            if (j - i + 1 <= max_len) break;
            if (is_palindrome(i, j)) {
                if (j - i + 1 > max_len) {
                    max_len = j - i + 1;
                    max_start = i;
                    max_end = j;
                }
                break;
            }
        }
    }

    printf("%d\n", max_len);

    int start = 0, end = 0;
    for (i = 0; i < len && end <= max_end; i++) {
        if (isalpha(text[i])) {
            if (start == max_start && end == max_end) break;
            if (start >= max_start) end++;
            if (start < max_start) start++;
        }
        putchar(text[i]);
    }
    printf("\n");

    return 0;
}