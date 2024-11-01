#include <stdio.h>
#include <string.h>

#define MAX_WORD_LENGTH 100
#define MAX_WORDS 20

int n;
char words[MAX_WORDS][MAX_WORD_LENGTH];
char start_letter;

int is_valid_connection(char *word1, char *word2) {
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    if (len1 > len2) return 0;
    for (int i = 0; i < len1; i++) {
        if (word1[i] != word2[len2 - len1 + i]) return 0;
    }
    return 1;
}

void dfs(int index, int current_length, int used[MAX_WORDS], int *max_length) {
    if (words[index][0] == start_letter) {
        if (current_length > *max_length) {
            *max_length = current_length;
        }
    }
    for (int i = 0; i < n; i++) {
        if (!used[i] && is_valid_connection(words[index], words[i])) {
            used[i] = 1;
            dfs(i, current_length + strlen(words[i]), used, max_length);
            used[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", words[i]);
    }
    scanf(" %c", &start_letter);

    int max_length = 0;
    int used[MAX_WORDS] = {0};
    for (int i = 0; i < n; i++) {
        if (is_valid_connection("", words[i])) {
            used[i] = 1;
            dfs(i, strlen(words[i]), used, &max_length);
            used[i] = 0;
        }
    }

    printf("%d\n", max_length);
    return 0;
}