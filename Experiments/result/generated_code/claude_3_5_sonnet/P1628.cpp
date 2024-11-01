#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 101
#define MAX_WORDS 100000

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    int N;
    scanf("%d", &N);

    char **words = (char **)malloc(N * sizeof(char *));
    for (int i = 0; i < N; i++) {
        words[i] = (char *)malloc(MAX_WORD_LENGTH * sizeof(char));
        scanf("%s", words[i]);
    }

    char prefix[MAX_WORD_LENGTH];
    scanf("%s", prefix);

    qsort(words, N, sizeof(char *), compare);

    int prefix_len = strlen(prefix);
    for (int i = 0; i < N; i++) {
        if (strncmp(words[i], prefix, prefix_len) == 0) {
            printf("%s\n", words[i]);
        }
    }

    for (int i = 0; i < N; i++) {
        free(words[i]);
    }
    free(words);

    return 0;
}