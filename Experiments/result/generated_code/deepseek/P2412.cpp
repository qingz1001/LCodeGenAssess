#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 16

int compare_words(const char *word1, const char *word2) {
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    int min_len = len1 < len2 ? len1 : len2;

    for (int i = 0; i < min_len; i++) {
        char c1 = tolower(word1[i]);
        char c2 = tolower(word2[i]);
        if (c1 != c2) {
            return c1 - c2;
        }
    }

    return len1 - len2;
}

int main() {
    int N, M;
    char words[MAX_WORDS][MAX_WORD_LEN];
    int queries[MAX_WORDS][2];

    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%s", words[i]);
    }
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &queries[i][0], &queries[i][1]);
    }

    for (int i = 0; i < M; i++) {
        int x = queries[i][0] - 1;
        int y = queries[i][1] - 1;
        char *max_word = words[x];

        for (int j = x + 1; j <= y; j++) {
            if (compare_words(words[j], max_word) > 0) {
                max_word = words[j];
            }
        }

        printf("%s\n", max_word);
    }

    return 0;
}