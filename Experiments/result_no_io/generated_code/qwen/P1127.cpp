#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 21
#define MAX_WORDS 1000

typedef struct {
    char word[MAX_WORD_LENGTH];
    int index;
} Word;

int compare(const void *a, const void *b) {
    return strcmp(((Word *)a)->word, ((Word *)b)->word);
}

int main() {
    int n;
    scanf("%d", &n);
    if (n == 0) {
        printf("***\n");
        return 0;
    }

    Word words[MAX_WORDS];
    for (int i = 0; i < n; i++) {
        scanf("%s", words[i].word);
        words[i].index = i;
    }

    qsort(words, n, sizeof(Word), compare);

    int visited[MAX_WORDS] = {0};
    int chain_length = 0;
    int start_index = -1;

    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        int current_index = i;
        while (!visited[current_index]) {
            visited[current_index] = 1;
            current_index++;
            while (current_index < n && !visited[current_index] && words[current_index].word[0] == words[current_index - 1].word[strlen(words[current_index - 1].word) - 1]) {
                current_index++;
            }
        }
        if (current_index - i > chain_length) {
            chain_length = current_index - i;
            start_index = i;
        }
    }

    if (chain_length == 0) {
        printf("***\n");
        return 0;
    }

    for (int i = start_index; i < start_index + chain_length; i++) {
        if (i != start_index) printf(".");
        printf("%s", words[i].word);
    }
    printf("\n");

    return 0;
}