#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 1000
#define MAX_LENGTH 10
#define MAX_BUTTONS 26

int B, L, D;
char words[MAX_WORDS][MAX_LENGTH + 1];
char buttons[MAX_BUTTONS][MAX_BUTTONS + 1];
int button_count[MAX_BUTTONS];

bool is_unique(char *word, int button_assignments[]) {
    int len = strlen(word);
    char sequence[MAX_LENGTH + 1] = {0};
    for (int i = 0; i < len; i++) {
        sequence[i] = button_assignments[word[i] - 'A'] + '0';
    }
    for (int i = 0; i < D; i++) {
        if (strcmp(words[i], word) != 0 && strncmp(words[i], sequence, len) == 0) {
            return false;
        }
    }
    return true;
}

int count_unique_words(int button_assignments[]) {
    int count = 0;
    for (int i = 0; i < D; i++) {
        if (is_unique(words[i], button_assignments)) {
            count++;
        }
    }
    return count;
}

void assign_buttons(int button, int start, int button_assignments[], int *max_unique) {
    if (button == B) {
        int unique_count = count_unique_words(button_assignments);
        if (unique_count > *max_unique) {
            *max_unique = unique_count;
            for (int i = 0; i < B; i++) {
                button_count[i] = 0;
                for (int j = 0; j < L; j++) {
                    if (button_assignments[j] == i) {
                        buttons[i][button_count[i]++] = 'A' + j;
                    }
                }
                buttons[i][button_count[i]] = '\0';
            }
        }
        return;
    }
    for (int i = start; i <= L - (B - button); i++) {
        for (int j = start; j <= i; j++) {
            button_assignments[j] = button;
        }
        assign_buttons(button + 1, i + 1, button_assignments, max_unique);
    }
}

int main() {
    scanf("%d %d", &B, &L);
    scanf("%d", &D);
    for (int i = 0; i < D; i++) {
        scanf("%s", words[i]);
    }

    int button_assignments[MAX_BUTTONS] = {0};
    int max_unique = 0;
    assign_buttons(0, 0, button_assignments, &max_unique);

    printf("%d\n", max_unique);
    for (int i = 0; i < B; i++) {
        printf("%s\n", buttons[i]);
    }

    return 0;
}