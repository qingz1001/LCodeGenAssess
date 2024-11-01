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

    char last_char = '\0';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!words[j].used && (last_char == '\0' || last_char == words[j].word[0])) {
                if (last_char != '\0') {
                    strcat(result, ".");
                }
                strcat(result, words[j].word);
                last_char = words[j].word[strlen(words[j].word) - 1];
                words[j].used = 1;
                break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (!words[i].used) {
            printf("***\n");
            return 0;
        }
    }

    printf("%s\n", result);
    return 0;
}