#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 11
#define MAX_LETTERS 26

char words[MAX_WORDS][MAX_WORD_LEN];
int word_count;
int buttons, letters;
char button_assignment[MAX_LETTERS + 1];
int max_unambiguous = 0;
char best_assignment[MAX_LETTERS + 1];

int is_unambiguous(const char* word) {
    char code[MAX_WORD_LEN] = {0};
    for (int i = 0; word[i]; i++) {
        code[i] = button_assignment[word[i] - 'A'];
    }
    
    for (int i = 0; i < word_count; i++) {
        if (strcmp(word, words[i]) == 0) continue;
        
        int match = 1;
        for (int j = 0; words[i][j]; j++) {
            if (code[j] != button_assignment[words[i][j] - 'A']) {
                match = 0;
                break;
            }
        }
        if (match) return 0;
    }
    return 1;
}

void count_unambiguous(int* count) {
    *count = 0;
    for (int i = 0; i < word_count; i++) {
        if (is_unambiguous(words[i])) {
            (*count)++;
        }
    }
}

void assign_buttons(int start, int button, int remaining) {
    if (button > buttons) return;
    
    if (remaining == 0) {
        int count;
        count_unambiguous(&count);
        if (count > max_unambiguous) {
            max_unambiguous = count;
            strcpy(best_assignment, button_assignment);
        }
        return;
    }
    
    for (int i = start; i <= letters - remaining + 1; i++) {
        memset(button_assignment + start, button + '0', i - start);
        assign_buttons(i, button + 1, remaining - (i - start));
    }
}

int main() {
    scanf("%d %d", &buttons, &letters);
    scanf("%d", &word_count);
    
    for (int i = 0; i < word_count; i++) {
        scanf("%s", words[i]);
    }
    
    assign_buttons(0, 1, letters);
    
    printf("%d\n", max_unambiguous);
    
    for (int i = 1; i <= buttons; i++) {
        for (int j = 0; j < letters; j++) {
            if (best_assignment[j] == i + '0') {
                printf("%c", 'A' + j);
            }
        }
        printf("\n");
    }
    
    return 0;
}