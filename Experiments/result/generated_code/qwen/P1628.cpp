#include <stdio.h>
#include <string.h>

#define MAX_WORD_LENGTH 100
#define MAX_N 100000

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    int N;
    scanf("%d", &N);

    char words[MAX_N][MAX_WORD_LENGTH + 1];
    for (int i = 0; i < N; i++) {
        scanf("%s", words[i]);
    }

    char T[MAX_WORD_LENGTH + 1];
    scanf("%s", T);

    qsort(words, N, sizeof(char *), compare);

    for (int i = 0; i < N; i++) {
        if (strncmp(words[i], T, strlen(T)) == 0) {
            printf("%s\n", words[i]);
        }
    }

    return 0;
}