#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_WORDS 2001

int n;
char word[MAX_N + 2];

int check_valid(char* w, int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        if (w[i] == '1') {
            sum += i + 1;
        }
    }
    return sum == 0 || sum % (len + 1) == 0;
}

void solve() {
    int len = strlen(word);
    char original[MAX_N + 2];

    // Case 4: No change
    if (len == n && check_valid(word, len)) {
        printf("%s\n", word);
        return;
    }

    // Case 1: Replace 0 with 1
    if (len == n) {
        for (int i = 0; i < n; i++) {
            if (word[i] == '1') {
                strcpy(original, word);
                original[i] = '0';
                if (check_valid(original, n)) {
                    printf("%s\n", original);
                    return;
                }
            }
        }
    }

    // Case 2: Delete a character
    if (len == n - 1) {
        for (int i = 0; i <= n - 1; i++) {
            strcpy(original, word);
            memmove(original + i + 1, original + i, n - i);
            original[i] = '0';
            if (check_valid(original, n)) {
                printf("%s\n", original);
                return;
            }
        }
        for (int i = 0; i <= n - 1; i++) {
            strcpy(original, word);
            memmove(original + i + 1, original + i, n - i);
            original[i] = '1';
            if (check_valid(original, n)) {
                printf("%s\n", original);
                return;
            }
        }
    }

    // Case 3: Insert a character
    if (len == n + 1) {
        for (int i = 0; i < n + 1; i++) {
            strcpy(original, word);
            memmove(original + i, original + i + 1, n - i);
            original[n] = '\0';
            if (check_valid(original, n)) {
                printf("%s\n", original);
                return;
            }
        }
    }

    printf("-1\n");
}

int main() {
    while (scanf("%d %s", &n, word) == 2) {
        solve();
    }
    return 0;
}