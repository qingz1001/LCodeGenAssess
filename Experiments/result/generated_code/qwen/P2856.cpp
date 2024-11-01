#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUTTONS 26
#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 10

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void solve(int B, int L, char **words, int *result_buttons, int *result_count) {
    qsort(words, L, sizeof(char *), compare);

    int used[MAX_BUTTONS] = {0};
    int current_button = 0;
    int count = 0;

    for (int i = 0; i < L; ++i) {
        int len = strlen(words[i]);
        if (len > 0) {
            result_buttons[current_button]++;
            count++;
            for (int j = 0; j < len; ++j) {
                int index = words[i][j] - 'A';
                if (!used[index]) {
                    used[index] = 1;
                    current_button++;
                    if (current_button == B) {
                        current_button = 0;
                    }
                }
            }
        }
    }

    *result_count = count;
}

int main() {
    int B, L;
    scanf("%d %d", &B, &L);

    char **words = (char **)malloc(L * sizeof(char *));
    for (int i = 0; i < L; ++i) {
        words[i] = (char *)malloc((MAX_WORD_LENGTH + 1) * sizeof(char));
        scanf("%s", words[i]);
    }

    int result_buttons[MAX_BUTTONS] = {0};
    int result_count;

    solve(B, L, words, result_buttons, &result_count);

    printf("%d\n", result_count);
    for (int i = 0; i < B; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (result_buttons[i] > 0 && !used[j]) {
                printf("%c", j + 'A');
                result_buttons[i]--;
                used[j] = 1;
            }
        }
        printf("\n");
    }

    for (int i = 0; i < L; ++i) {
        free(words[i]);
    }
    free(words);

    return 0;
}