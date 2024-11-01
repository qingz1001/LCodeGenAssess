#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUTTONS 26
#define MAX_LETTERS 26
#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 11

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void print_buttons(char *buttons[MAX_BUTTONS], int num_buttons) {
    for (int i = 0; i < num_buttons; i++) {
        printf("%s\n", buttons[i]);
    }
}

int main() {
    int B, L;
    scanf("%d %d", &B, &L);

    char **words = malloc(MAX_WORDS * sizeof(char *));
    for (int i = 0; i < MAX_WORDS; i++) {
        words[i] = malloc(MAX_WORD_LENGTH * sizeof(char));
    }

    int num_words = 0;
    while (scanf("%s", words[num_words]) != EOF) {
        num_words++;
    }

    qsort(words, num_words, sizeof(char *), compare);

    char *buttons[MAX_BUTTONS];
    for (int i = 0; i < B; i++) {
        buttons[i] = malloc((L / B + 1) * sizeof(char));
    }

    int index = 0;
    for (int i = 0; i < B; i++) {
        int start = 'A' + index * (L / B);
        int end = start + (i == B - 1 ? L : L / B) - 1;
        sprintf(buttons[i], "%c-%c", start, end);
        index++;
    }

    int unique_count = 0;
    for (int i = 0; i < num_words; i++) {
        char *word = words[i];
        int len = strlen(word);
        int sequence[10];
        memset(sequence, 0, sizeof(sequence));

        for (int j = 0; j < len; j++) {
            int pos = word[j] - 'A';
            int button_index = pos / (L / B);
            sequence[j] = button_index + 1;
        }

        int is_unique = 1;
        for (int j = 0; j < i; j++) {
            if (strcmp(words[j], word) == 0 && !memcmp(sequence, words[j] - 'A', len)) {
                is_unique = 0;
                break;
            }
        }

        if (is_unique) {
            unique_count++;
        }
    }

    printf("%d\n", unique_count);
    print_buttons(buttons, B);

    for (int i = 0; i < num_words; i++) {
        free(words[i]);
    }
    for (int i = 0; i < B; i++) {
        free(buttons[i]);
    }
    free(words);
    free(buttons);

    return 0;
}