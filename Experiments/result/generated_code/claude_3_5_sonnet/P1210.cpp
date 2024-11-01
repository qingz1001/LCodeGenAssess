#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 20000
#define MAX_PALINDROME 2000

char input[MAX_LEN];
char stripped[MAX_LEN];
int len, stripped_len;

int is_palindrome(int start, int end) {
    while (start < end) {
        if (stripped[start] != stripped[end]) return 0;
        start++;
        end--;
    }
    return 1;
}

int main() {
    char c;
    int i = 0, j = 0;
    while ((c = getchar()) != EOF && i < MAX_LEN - 1) {
        input[i++] = c;
        if (isalpha(c)) stripped[j++] = tolower(c);
    }
    input[i] = '\0';
    len = i;
    stripped_len = j;

    int max_len = 0, max_start = 0, max_end = 0;
    for (i = 0; i < stripped_len; i++) {
        for (j = i; j < stripped_len; j++) {
            if (j - i + 1 > max_len && is_palindrome(i, j)) {
                max_len = j - i + 1;
                max_start = i;
                max_end = j;
            }
        }
    }

    printf("%d\n", max_len);

    int input_start = 0, input_end = 0;
    for (i = 0, j = 0; i < len && j <= max_end; i++) {
        if (isalpha(input[i])) {
            if (j == max_start) input_start = i;
            if (j == max_end) input_end = i;
            j++;
        }
    }

    for (i = input_start; i <= input_end; i++) {
        putchar(input[i]);
    }
    putchar('\n');

    return 0;
}