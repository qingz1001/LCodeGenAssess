#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX_WORDS 2001

int n;
char words[MAX_WORDS][MAX_N + 1];

int check_validity(const char *word) {
    int sum = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == '1') {
            sum += i + 1;
        }
    }
    return sum % (n + 1) == 0 || sum == 0;
}

void recover_word(char *original, const char *transformed) {
    int len = strlen(transformed);
    int pos = 0;

    while (pos < len) {
        if (transformed[pos] == original[pos]) {
            pos++;
        } else if (transformed[pos] == '1' && original[pos] == '0') {
            // Operation 1: Replace 0 with 1
            original[pos] = '1';
            pos++;
        } else if (transformed[pos] == '0') {
            // Operation 2: Delete a symbol
            memmove(&original[pos], &original[pos + 1], len - pos);
            len--;
        } else {
            // Operation 3: Insert a symbol
            memmove(&original[pos + 1], &original[pos], len - pos);
            original[pos++] = transformed[pos];
            len++;
        }
    }

    // Ensure the word is valid after recovery
    if (!check_validity(original)) {
        printf("-1\n");
        exit(0);
    }
}

int main() {
    scanf("%d", &n);

    int word_count = 0;
    while (scanf(" %s", words[word_count]) == 1) {
        word_count++;
    }

    for (int i = 0; i < word_count; i++) {
        char original[MAX_N + 1];
        strcpy(original, words[i]);

        recover_word(original, words[i]);
        printf("%s\n", original);
    }

    return 0;
}