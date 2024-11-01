#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_N 100001
#define MAX_LEN 16

char words[MAX_N][MAX_LEN];
int N, M;

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%s", words[i]);
        for (int j = 0; words[i][j]; j++) {
            words[i][j] = tolower(words[i][j]);
        }
    }

    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--; // Convert to zero-based index
        char max_word[MAX_LEN];
        strcpy(max_word, words[x]);
        for (int j = x + 1; j <= y; j++) {
            if (strcmp(words[j], max_word) > 0) {
                strcpy(max_word, words[j]);
            }
        }
        printf("%s\n", max_word);
    }

    return 0;
}