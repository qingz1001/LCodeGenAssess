#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 21

typedef struct {
    char word[MAX_WORD_LEN];
    int used;
} Word;

int compare(const void *a, const void *b) {
    return strcmp(((Word *)a)->word, ((Word *)b)->word);
}

int main() {
    int n;
    scanf("%d", &n);

    Word words[MAX_WORDS];
    for (int i = 0; i < n; i++) {
        scanf("%s", words[i].word);
        words[i].used = 0;
    }

    qsort(words, n, sizeof(Word), compare);

    char result[MAX_WORDS * (MAX_WORD_LEN + 1)];
    result[0] = '\0';

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strlen(result) == 0 || result[strlen(result) - 1] == words[i].word[0]) {
            strcat(result, words[i].word);
            strcat(result, ".");
            words[i].used = 1;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("***\n");
        return 0;
    }

    while (1) {
        found = 0;
        for (int i = 0; i < n; i++) {
            if (!words[i].used && result[strlen(result) - 2] == words[i].word[0]) {
                strcat(result, words[i].word);
                strcat(result, ".");
                words[i].used = 1;
                found = 1;
                break;
            }
        }
        if (!found) break;
    }

    result[strlen(result) - 1] = '\0'; // Remove the trailing dot
    printf("%s\n", result);

    return 0;
}