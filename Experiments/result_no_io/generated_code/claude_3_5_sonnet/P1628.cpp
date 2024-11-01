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
    char *words[MAX_WORDS];
    char T[MAX_WORD_LENGTH];

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        words[i] = (char *)malloc(MAX_WORD_LENGTH * sizeof(char));
        scanf("%s", words[i]);
    }

    scanf("%s", T);

    qsort(words, N, sizeof(char *), compare);

    int T_len = strlen(T);
    for (int i = 0; i < N; i++) {
        if (strncmp(words[i], T, T_len) == 0) {
            printf("%s\n", words[i]);
        }
    }

    for (int i = 0; i < N; i++) {
        free(words[i]);
    }

    return 0;
}