#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 21

char words[MAX_WORDS][MAX_WORD_LEN];
int n;
int used[MAX_WORDS];
char result[MAX_WORDS * MAX_WORD_LEN];

int compare(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
}

int dfs(int index, char last_char, char *current) {
    if (index == n) {
        strcpy(result, current);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (!used[i] && (last_char == 0 || words[i][0] == last_char)) {
            used[i] = 1;
            int len = strlen(current);
            if (len > 0) {
                current[len] = '.';
                current[len + 1] = '\0';
            }
            strcat(current, words[i]);
            if (dfs(index + 1, words[i][strlen(words[i]) - 1], current)) {
                return 1;
            }
            used[i] = 0;
            current[len] = '\0';
        }
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", words[i]);
    }

    qsort(words, n, sizeof(words[0]), compare);

    char current[MAX_WORDS * MAX_WORD_LEN] = {0};
    if (dfs(0, 0, current)) {
        printf("%s\n", result);
    } else {
        printf("***\n");
    }

    return 0;
}