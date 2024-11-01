#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 21
#define MAX_CODE_LENGTH 101

char words[MAX_WORDS][MAX_WORD_LENGTH];
char code[MAX_CODE_LENGTH];
char solution[MAX_CODE_LENGTH];
int N;

const char* phone_map[] = {"", "abc", "def", "ghi", "jkl", "mn", "opq", "rst", "uvw", "xyz"};

bool match_word(const char* word, const char* code) {
    while (*word && *code) {
        if (strchr(phone_map[*code - '0'], *word) == NULL) {
            return false;
        }
        word++;
        code++;
    }
    return *word == '\0' && *code == '\0';
}

bool solve(int start) {
    if (start >= strlen(code)) {
        return true;
    }
    
    for (int i = 0; i < N; i++) {
        int len = strlen(words[i]);
        if (start + len <= strlen(code) && match_word(words[i], code + start)) {
            strcat(solution, words[i]);
            strcat(solution, " ");
            if (solve(start + len)) {
                return true;
            }
            solution[strlen(solution) - len - 1] = '\0';
        }
    }
    
    return false;
}

int main() {
    scanf("%d", &N);
    scanf("%s", code);
    
    for (int i = 0; i < N; i++) {
        scanf("%s", words[i]);
    }
    
    solution[0] = '\0';
    
    if (solve(0)) {
        solution[strlen(solution) - 1] = '\0';  // Remove the last space
        printf("%s\n", solution);
    } else {
        printf("No Solutions!\n");
    }
    
    return 0;
}