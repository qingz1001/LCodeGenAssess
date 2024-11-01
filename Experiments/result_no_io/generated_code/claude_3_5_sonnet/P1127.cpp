#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 21

char words[MAX_WORDS][MAX_WORD_LENGTH];
int n;
int used[MAX_WORDS];
char result[MAX_WORDS * MAX_WORD_LENGTH];

int compare(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
}

void dfs(int index, char *current) {
    if (index == n) {
        strcpy(result, current);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!used[i] && (index == 0 || words[i][0] == current[strlen(current) - 1])) {
            used[i] = 1;
            char temp[MAX_WORDS * MAX_WORD_LENGTH];
            if (index == 0)
                strcpy(temp, words[i]);
            else
                sprintf(temp, "%s.%s", current, words[i]);
            dfs(index + 1, temp);
            if (result[0]) return;
            used[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", words[i]);
    }

    qsort(words, n, sizeof(words[0]), compare);

    dfs(0, "");

    if (result[0])
        printf("%s\n", result);
    else
        printf("***\n");

    return 0;
}