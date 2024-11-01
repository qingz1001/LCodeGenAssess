#include <stdio.h>
#include <string.h>

#define MAX_N 1000
#define MAX_WORDS 2001

int is_valid(char *word, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (word[i] == '1') {
            sum += (i + 1);
        }
    }
    return sum == 0 || sum % (n + 1) == 0;
}

void solve(int n, char *word) {
    int len = strlen(word);

    // Case 4: No change
    if (is_valid(word, len)) {
        printf("%s\n", word);
        return;
    }

    // Case 1: Replace a 0 with a 1
    for (int i = 0; i < len; i++) {
        if (word[i] == '0') {
            word[i] = '1';
            if (is_valid(word, len)) {
                printf("%s\n", word);
                return;
            }
            word[i] = '0'; // revert change
        }
    }

    // Case 2: Delete a character
    for (int i = 0; i < len; i++) {
        char temp = word[i];
        memmove(&word[i], &word[i + 1], len - i);
        if (is_valid(word, len - 1)) {
            printf("%s\n", word);
            return;
        }
        memmove(&word[i], &word[i + 1], len - i - 1);
        word[len - 1] = temp;
    }

    // Case 3: Insert a character
    for (int i = 0; i <= len; i++) {
        for (char c = '0'; c <= '1'; c++) {
            memmove(&word[i + 1], &word[i], len - i + 1);
            word[i] = c;
            if (is_valid(word, len + 1)) {
                printf("%s\n", word);
                return;
            }
            memmove(&word[i], &word[i + 1], len - i + 1);
        }
    }

    // No solution
    printf("-1\n");
}

int main() {
    int n;
    char word[MAX_N + 2];

    while (scanf("%d %s", &n, word) != EOF) {
        solve(n, word);
    }

    return 0;
}