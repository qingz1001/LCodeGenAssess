#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 16
#define MAX_QUERIES 1000

typedef struct {
    char word[MAX_WORD_LENGTH];
} Word;

int compare(const void *a, const void *b) {
    return strcmp(((Word *)b)->word, ((Word *)a)->word);
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    Word words[N];
    for (int i = 0; i < N; i++) {
        scanf("%s", words[i].word);
        for (char *p = words[i].word; *p != '\0'; p++) {
            *p = tolower(*p);
        }
    }

    for (int q = 0; q < M; q++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--;
        y--;

        qsort(&words[x], y - x + 1, sizeof(Word), compare);

        printf("%s\n", words[x].word);
    }

    return 0;
}