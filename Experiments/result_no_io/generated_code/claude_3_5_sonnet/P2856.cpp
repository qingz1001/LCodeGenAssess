#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 11
#define MAX_LETTERS 26

char words[MAX_WORDS][MAX_WORD_LEN];
int word_count;
int buttons, letters;
int best_assignment[MAX_LETTERS];
int current_assignment[MAX_LETTERS];
int max_unambiguous = 0;

int get_button(char c) {
    return current_assignment[c - 'A'];
}

bool is_unambiguous(const char *word) {
    for (int i = 0; i < word_count; i++) {
        if (strcmp(word, words[i]) == 0) continue;
        bool same = true;
        for (int j = 0; word[j] && words[i][j]; j++) {
            if (get_button(word[j]) != get_button(words[i][j])) {
                same = false;
                break;
            }
        }
        if (same) return false;
    }
    return true;
}

int count_unambiguous() {
    int count = 0;
    for (int i = 0; i < word_count; i++) {
        if (is_unambiguous(words[i])) count++;
    }
    return count;
}

void update_best() {
    int unambiguous = count_unambiguous();
    if (unambiguous > max_unambiguous) {
        max_unambiguous = unambiguous;
        memcpy(best_assignment, current_assignment, sizeof(current_assignment));
    }
}

void assign(int letter, int button) {
    if (letter == letters) {
        update_best();
        return;
    }
    
    if (button < buttons) {
        for (int i = letter; i < letters; i++) {
            for (int j = letter; j <= i; j++) {
                current_assignment[j] = button;
            }
            assign(i + 1, button + 1);
        }
    }
    
    if (button > 1) {
        current_assignment[letter] = button - 1;
        assign(letter + 1, button);
    }
}

int main() {
    scanf("%d %d", &buttons, &letters);
    scanf("%d", &word_count);
    
    for (int i = 0; i < word_count; i++) {
        scanf("%s", words[i]);
    }
    
    assign(0, 1);
    
    printf("%d\n", max_unambiguous);
    
    int current_button = 1;
    for (int i = 0; i < letters; i++) {
        if (best_assignment[i] != current_button) {
            printf("\n");
            current_button = best_assignment[i];
        }
        printf("%c", 'A' + i);
    }
    printf("\n");
    
    return 0;
}