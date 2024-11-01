#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 16
#define MAX_WORDS 10000
#define MAX_QUERIES 10000

typedef struct {
    char word[MAX_WORD_LENGTH];
} Word;

int compareWords(const void *a, const void *b) {
    Word *wordA = (Word *)a;
    Word *wordB = (Word *)b;
    int lenA = strlen(wordA->word);
    int lenB = strlen(wordB->word);
    for (int i = 0; i < lenA && i < lenB; i++) {
        if (tolower(wordA->word[i]) != tolower(wordB->word[i])) {
            return tolower(wordB->word[i]) - tolower(wordA->word[i]);
        }
    }
    return lenB - lenA;
}

void findMaxWord(Word words[], int start, int end, char result[]) {
    qsort(words + start, end - start + 1, sizeof(Word), compareWords);
    strcpy(result, words[start].word);
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    Word words[N];
    for (int i = 0; i < N; i++) {
        scanf("%s", words[i].word);
    }

    char results[M][MAX_WORD_LENGTH];
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        findMaxWord(words, x - 1, y - 1, results[i]);
    }

    for (int i = 0; i < M; i++) {
        printf("%s\n", results[i]);
    }

    return 0;
}