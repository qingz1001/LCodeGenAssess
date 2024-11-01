#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100000
#define MAX_WORD_LENGTH 100

int cmp(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    int n;
    scanf("%d", &n);

    char **words = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        words[i] = (char *)malloc(MAX_WORD_LENGTH * sizeof(char));
        scanf("%s", words[i]);
    }

    char t[MAX_WORD_LENGTH];
    scanf("%s", t);

    qsort(words, n, sizeof(char *), cmp);

    for (int i = 0; i < n; i++) {
        if (strncmp(words[i], t, strlen(t)) == 0) {
            printf("%s\n", words[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        free(words[i]);
    }
    free(words);

    return 0;
}