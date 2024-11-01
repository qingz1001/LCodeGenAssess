#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 20
#define MAX_PASSWORD_LENGTH 100

const char *keypad[] = {
    "", "", "abc", "def", "ghi", "jkl",
    "mno", "pqrs", "tuv", "wxyz"
};

void dfs(const char *password, int index, const char **words, int word_count, char *result, int result_index) {
    if (index == strlen(password)) {
        result[result_index] = '\0';
        printf("%s\n", result);
        return;
    }

    int digit = password[index] - '0';
    for (int i = 0; i < strlen(keypad[digit]); i++) {
        char ch = keypad[digit][i];
        result[result_index++] = ch;
        dfs(password, index + 1, words, word_count, result, result_index);
        result[--result_index] = '\0';
    }
}

int main() {
    int N;
    scanf("%d", &N);

    char password[MAX_PASSWORD_LENGTH + 1];
    scanf("%s", password);

    const char *words[MAX_WORDS];
    for (int i = 0; i < N; i++) {
        words[i] = malloc(MAX_WORD_LENGTH + 1);
        scanf("%s", (char *)words[i]);
    }

    char result[MAX_PASSWORD_LENGTH + 1];
    dfs(password, 0, words, N, result, 0);

    // Free allocated memory
    for (int i = 0; i < N; i++) {
        free((char *)words[i]);
    }

    return 0;
}