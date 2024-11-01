#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 20
#define MAX_DIGITS 100

char digit_to_chars[10][4] = {
    "",     // 0
    "",     // 1
    "abc",  // 2
    "def",  // 3
    "ghi",  // 4
    "jkl",  // 5
    "mno",  // 6
    "pqrs", // 7
    "tuv",  // 8
    "wxyz"  // 9
};

int is_match(char *word, char *digits, int start, int len) {
    for (int i = 0; i < len; i++) {
        int digit = digits[start + i] - '0';
        int found = 0;
        for (int j = 0; digit_to_chars[digit][j]; j++) {
            if (digit_to_chars[digit][j] == word[i]) {
                found = 1;
                break;
            }
        }
        if (!found) return 0;
    }
    return 1;
}

int main() {
    int N;
    char digits[MAX_DIGITS + 1];
    char words[MAX_WORDS][MAX_WORD_LEN + 1];

    scanf("%d", &N);
    scanf("%s", digits);
    for (int i = 0; i < N; i++) {
        scanf("%s", words[i]);
    }

    int len = strlen(digits);
    int found = 0;

    for (int i = 0; i < N; i++) {
        int word_len = strlen(words[i]);
        if (word_len <= len && is_match(words[i], digits, 0, word_len)) {
            printf("%s", words[i]);
            found = 1;
            int remaining_len = len - word_len;
            int j = word_len;
            while (remaining_len > 0) {
                int matched = 0;
                for (int k = 0; k < N; k++) {
                    int next_word_len = strlen(words[k]);
                    if (next_word_len <= remaining_len && is_match(words[k], digits, j, next_word_len)) {
                        printf(" %s", words[k]);
                        j += next_word_len;
                        remaining_len -= next_word_len;
                        matched = 1;
                        break;
                    }
                }
                if (!matched) break;
            }
            if (remaining_len == 0) break;
        }
    }

    if (!found) {
        printf("No Solutions!");
    }

    return 0;
}