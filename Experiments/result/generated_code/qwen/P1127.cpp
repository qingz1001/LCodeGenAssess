#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 21
#define MAX_WORDS 1001

typedef struct {
    char word[MAX_WORD_LEN];
    int index;
} Word;

int compare(const void *a, const void *b) {
    return strcmp(((Word *)a)->word, ((Word *)b)->word);
}

int canConnect(char *x, char *y) {
    int lenX = strlen(x);
    int lenY = strlen(y);
    if (lenX == 0 || lenY == 0) return 0;
    return x[lenX - 1] == y[0];
}

void findChain(Word words[], int n, int start, int *chain, int *chainLen, int *minChainLen, char **result) {
    chain[*chainLen] = start;
    (*chainLen)++;
    if (*chainLen > *minChainLen) return;

    for (int i = 0; i < n; i++) {
        if (canConnect(words[start].word, words[i].word) && !chain[i]) {
            findChain(words, n, i, chain, chainLen, minChainLen, result);
        }
    }

    if (*chainLen > *minChainLen) {
        *minChainLen = *chainLen;
        free(*result);
        *result = malloc((*minChainLen + 1) * sizeof(char));
        strcpy(*result, "");
        for (int i = 0; i < *minChainLen; i++) {
            strcat(*result, words[chain[i]].word);
            if (i != *minChainLen - 1) strcat(*result, ".");
        }
    }

    (*chainLen)--;
}

int main() {
    int n;
    scanf("%d", &n);
    Word words[MAX_WORDS];
    for (int i = 0; i < n; i++) {
        scanf("%s", words[i].word);
        words[i].index = i;
    }

    qsort(words, n, sizeof(Word), compare);

    int *chain = calloc(n, sizeof(int));
    int chainLen = 0;
    int minChainLen = INT_MAX;
    char *result = NULL;

    for (int i = 0; i < n; i++) {
        if (!chain[i]) {
            findChain(words, n, i, chain, &chainLen, &minChainLen, &result);
        }
    }

    free(chain);

    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("***\n");
    }

    return 0;
}