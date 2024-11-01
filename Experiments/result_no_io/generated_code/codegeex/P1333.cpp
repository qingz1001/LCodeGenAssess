#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STICKS 250000
#define MAX_WORD_LENGTH 11

typedef struct {
    char start[MAX_WORD_LENGTH];
    char end[MAX_WORD_LENGTH];
} Stick;

Stick sticks[MAX_STICKS];
int count[MAX_WORD_LENGTH];
int visited[MAX_STICKS];
int n;

int compare(const void *a, const void *b) {
    Stick *stickA = (Stick *)a;
    Stick *stickB = (Stick *)b;
    return strcmp(stickA->start, stickB->start);
}

int dfs(int stick) {
    if (visited[stick]) return 0;
    visited[stick] = 1;
    return dfs(count[sticks[stick].end]);
}

int main() {
    char word1[MAX_WORD_LENGTH], word2[MAX_WORD_LENGTH];
    int i, j;

    while (scanf("%s %s", word1, word2) != EOF) {
        for (i = 0; i < n; i++) {
            if (strcmp(sticks[i].start, word1) == 0 && strcmp(sticks[i].end, word2) == 0) {
                break;
            }
        }
        if (i == n) {
            strcpy(sticks[n].start, word1);
            strcpy(sticks[n].end, word2);
            n++;
        }
    }

    qsort(sticks, n, sizeof(Stick), compare);

    for (i = 0; i < n; i++) {
        if (count[sticks[i].start] == 0) {
            for (j = 0; j < n; j++) {
                if (strcmp(sticks[j].end, sticks[i].start) == 0) {
                    count[sticks[j].start] = i;
                }
            }
        }
    }

    memset(visited, 0, sizeof(visited));
    if (dfs(count[sticks[0].start])) {
        printf("Possible\n");
    } else {
        printf("Impossible\n");
    }

    return 0;
}