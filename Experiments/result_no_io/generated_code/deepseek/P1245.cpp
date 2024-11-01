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

int can_translate(char *word, char *digits, int *index) {
    int i = 0;
    while (word[i] != '\0' && digits[*index] != '\0') {
        int digit = digits[*index] - '0';
        int found = 0;
        for (int j = 0; digit_to_chars[digit][j] != '\0'; j++) {
            if (word[i] == digit_to_chars[digit][j]) {
                found = 1;
                break;
            }
        }
        if (!found) return 0;
        i++;
        (*index)++;
    }
    return word[i] == '\0';
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

    for (int i = 0; i < N; i++) {
        int index = 0;
        if (can_translate(words[i], digits, &index)) {
            printf("%s\n", words[i]);
            return 0;
        }
    }

    printf("No Solutions!\n");
    return 0;
}