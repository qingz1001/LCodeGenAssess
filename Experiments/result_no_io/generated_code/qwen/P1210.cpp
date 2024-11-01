#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 20000

int is_palindrome(char *str, int len) {
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

void find_longest_palindrome(char *input, char *output, int *length) {
    int max_len = 0;
    int start = 0;

    for (int i = 0; input[i]; i++) {
        for (int j = i + max_len; j <= strlen(input); j++) {
            char temp[MAX_LEN];
            strncpy(temp, input + i, j - i);
            temp[j - i] = '\0';
            if (is_palindrome(temp, j - i)) {
                if (j - i > max_len) {
                    max_len = j - i;
                    start = i;
                }
            }
        }
    }

    *length = max_len;
    strncpy(output, input + start, max_len);
    output[max_len] = '\0';
}

int main() {
    char input[MAX_LEN];
    char output[MAX_LEN];
    int length;

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    find_longest_palindrome(input, output, &length);

    printf("%d\n", length);
    printf("%s\n", output);

    return 0;
}