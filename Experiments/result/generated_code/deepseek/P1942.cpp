#include <stdio.h>
#include <string.h>

int is_valid(char *word, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (word[i] == '1') {
            sum += i + 1;
        }
    }
    return sum == 0 || sum % (n + 1) == 0;
}

void solve(int n, char *word) {
    int len = strlen(word);

    // Check for no change
    if (is_valid(word, len)) {
        printf("%s\n", word);
        return;
    }

    // Check for insertion
    for (int i = 0; i <= len; i++) {
        for (char c = '0'; c <= '1'; c++) {
            char temp[1002];
            strncpy(temp, word, i);
            temp[i] = c;
            strcpy(temp + i + 1, word + i);
            if (is_valid(temp, len + 1)) {
                printf("%s\n", temp);
                return;
            }
        }
    }

    // Check for deletion
    for (int i = 0; i < len; i++) {
        char temp[1002];
        strncpy(temp, word, i);
        strcpy(temp + i, word + i + 1);
        if (is_valid(temp, len - 1)) {
            printf("%s\n", temp);
            return;
        }
    }

    // Check for replacement
    for (int i = 0; i < len; i++) {
        char original = word[i];
        for (char c = '0'; c <= '1'; c++) {
            if (c != original) {
                word[i] = c;
                if (is_valid(word, len)) {
                    printf("%s\n", word);
                    return;
                }
                word[i] = original;
            }
        }
    }

    // No solution
    printf("-1\n");
}

int main() {
    int n;
    char word[1002];

    while (scanf("%d", &n) != EOF) {
        scanf("%s", word);
        solve(n, word);
    }

    return 0;
}