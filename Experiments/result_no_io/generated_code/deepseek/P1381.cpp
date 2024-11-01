#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX_M 100000
#define MAX_WORD_LEN 10

typedef struct {
    char word[MAX_WORD_LEN + 1];
} Word;

int isInList(Word *list, int size, char *word) {
    for (int i = 0; i < size; i++) {
        if (strcmp(list[i].word, word) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int n, m;
    Word toLearn[MAX_N];
    Word article[MAX_M];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", toLearn[i].word);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%s", article[i].word);
    }

    int maxCount = 0;
    int minLength = MAX_M + 1;

    for (int i = 0; i < m; i++) {
        int count = 0;
        int seen[MAX_N] = {0};
        int length = 0;

        for (int j = i; j < m; j++) {
            if (isInList(toLearn, n, article[j].word)) {
                int index = -1;
                for (int k = 0; k < n; k++) {
                    if (strcmp(toLearn[k].word, article[j].word) == 0) {
                        index = k;
                        break;
                    }
                }
                if (index != -1 && !seen[index]) {
                    seen[index] = 1;
                    count++;
                }
            }
            length++;

            if (count == n) {
                if (count > maxCount || (count == maxCount && length < minLength)) {
                    maxCount = count;
                    minLength = length;
                }
                break;
            }
        }
    }

    printf("%d\n%d\n", maxCount, minLength);

    return 0;
}