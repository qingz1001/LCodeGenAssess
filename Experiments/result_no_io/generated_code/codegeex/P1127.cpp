#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 21
#define MAX_WORDS 1001

typedef struct {
    char word[MAX_WORD_LEN];
    int start;
    int end;
} Word;

int compare(const void *a, const void *b) {
    Word *wordA = (Word *)a;
    Word *wordB = (Word *)b;
    return strcmp(wordA->word, wordB->word);
}

int main() {
    int n;
    scanf("%d", &n);
    Word words[MAX_WORDS];
    for (int i = 0; i < n; i++) {
        scanf("%s", words[i].word);
        words[i].start = words[i].word[0];
        words[i].end = words[i].word[strlen(words[i].word) - 1];
    }

    qsort(words, n, sizeof(Word), compare);

    char start = words[0].start;
    char end = words[n-1].end;

    int *visited = (int *)calloc(n, sizeof(int));
    int *path = (int *)calloc(n, sizeof(int));
    int pathIndex = 0;

    int result = 0;
    for (int i = 0; i < n; i++) {
        if (words[i].start == start) {
            path[pathIndex++] = i;
            visited[i] = 1;
            if (dfs(words, visited, path, pathIndex, end, i)) {
                result = 1;
                break;
            }
            pathIndex--;
            visited[i] = 0;
        }
    }

    if (!result) {
        printf("***\n");
    } else {
        for (int i = 0; i < pathIndex; i++) {
            printf("%s", words[path[i]].word);
            if (i != pathIndex - 1) {
                printf(".");
            }
        }
        printf("\n");
    }

    free(visited);
    free(path);

    return 0;
}

int dfs(Word words[], int visited[], int path[], int pathIndex, char end, int currentIndex) {
    if (words[currentIndex].end == end) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && words[i].start == words[currentIndex].end) {
            path[pathIndex++] = i;
            visited[i] = 1;
            if (dfs(words, visited, path, pathIndex, end, i)) {
                return 1;
            }
            pathIndex--;
            visited[i] = 0;
        }
    }

    return 0;
}