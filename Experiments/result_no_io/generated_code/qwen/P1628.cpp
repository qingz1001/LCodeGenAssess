#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100
#define MAX_N 100000

typedef struct {
    char word[MAX_WORD_LENGTH];
} Word;

int compare(const void *a, const void *b) {
    return strcmp(((Word *)a)->word, ((Word *)b)->word);
}

int main() {
    int N;
    scanf("%d", &N);

    Word words[N];
    for (int i = 0; i < N; i++) {
        scanf("%s", words[i].word);
    }

    char T[MAX_WORD_LENGTH];
    scanf("%s", T);

    // Filter words that start with T
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (strncmp(words[i].word, T, strlen(T)) == 0) {
            words[count++] = words[i];
        }
    }

    // Sort the filtered words
    qsort(words, count, sizeof(Word), compare);

    // Output the sorted words
    for (int i = 0; i < count; i++) {
        printf("%s\n", words[i].word);
    }

    return 0;
}