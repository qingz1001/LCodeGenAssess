#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 21
#define MAX_CODE_LEN 101

char words[MAX_WORDS][MAX_WORD_LEN];
char code[MAX_CODE_LEN];
int N;
char result[MAX_CODE_LEN * 2];
bool solved = false;

char* keypad[] = {"", "abc", "def", "ghi", "jkl", "mn", "opq", "rst", "uvw", "xyz"};

bool match(char* word, char* code, int len) {
    for (int i = 0; i < len; i++) {
        if (strchr(keypad[code[i] - '0'], word[i]) == NULL) {
            return false;
        }
    }
    return true;
}

void solve(int pos, int len) {
    if (solved) return;
    if (pos == len) {
        solved = true;
        return;
    }
    
    for (int i = 0; i < N; i++) {
        int word_len = strlen(words[i]);
        if (pos + word_len <= len && match(words[i], code + pos, word_len)) {
            strcat(result, words[i]);
            strcat(result, " ");
            solve(pos + word_len, len);
            if (solved) return;
            result[strlen(result) - word_len - 1] = '\0';
        }
    }
}

int main() {
    scanf("%d", &N);
    scanf("%s", code);
    
    for (int i = 0; i < N; i++) {
        scanf("%s", words[i]);
    }
    
    solve(0, strlen(code));
    
    if (solved) {
        result[strlen(result) - 1] = '\0';  // Remove the last space
        printf("%s\n", result);
    } else {
        printf("No Solutions!\n");
    }
    
    return 0;
}