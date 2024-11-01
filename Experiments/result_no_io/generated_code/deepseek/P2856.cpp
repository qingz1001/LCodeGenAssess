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

bool is_unique(char *word, int button_assignments[26]) {
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (button_assignments[word[i] - 'A'] == button_assignments[word[j] - 'A']) {
                return false;
            }
        }
    }
    return true;
}

int count_unique_words(int button_assignments[26]) {
    int count = 0;
    for (int i = 0; i < D; i++) {
        if (is_unique(words[i], button_assignments)) {
            count++;
        }
    }
    return count;
}

void assign_buttons(int button_assignments[26], int button, int letter, int *max_unique, int best_assignments[26]) {
    if (button == B) {
        int unique_count = count_unique_words(button_assignments);
        if (unique_count > *max_unique) {
            *max_unique = unique_count;
            memcpy(best_assignments, button_assignments, sizeof(int) * 26);
        }
        return;
    }

    for (int i = letter; i <= L - (B - button); i++) {
        for (int j = i; j < L; j++) {
            for (int k = i; k <= j; k++) {
                button_assignments[k] = button;
            }
            assign_buttons(button_assignments, button + 1, j + 1, max_unique, best_assignments);
            for (int k = i; k <= j; k++) {
                button_assignments[k] = -1;
            }
        }
    }
}

int main() {
    scanf("%d %d", &B, &L);
    scanf("%d", &D);

    for (int i = 0; i < D; i++) {
        scanf("%s", words[i]);
    }

    int button_assignments[26];
    int best_assignments[26];
    int max_unique = 0;

    memset(button_assignments, -1, sizeof(button_assignments));
    assign_buttons(button_assignments, 0, 0, &max_unique, best_assignments);

    printf("%d\n", max_unique);
    for (int i = 0; i < B; i++) {
        for (int j = 0; j < 26; j++) {
            if (best_assignments[j] == i) {
                printf("%c", 'A' + j);
            }
        }
        printf("\n");
    }

    return 0;
}