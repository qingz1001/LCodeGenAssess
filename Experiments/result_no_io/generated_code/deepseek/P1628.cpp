#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 101
#define MAX_N 100000

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    int N;
    char words[MAX_N][MAX_WORD_LEN];
    char *sorted_words[MAX_N];
    char T[MAX_WORD_LEN];

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s", words[i]);
        sorted_words[i] = words[i];
    }
    scanf("%s", T);

    qsort(sorted_words, N, sizeof(char *), compare);

    for (int i = 0; i < N; i++) {
        if (strncmp(sorted_words[i], T, strlen(T)) == 0) {
            printf("%s\n", sorted_words[i]);
        }
    }

    return 0;
}