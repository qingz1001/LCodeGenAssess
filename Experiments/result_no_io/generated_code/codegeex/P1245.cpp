#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 20
#define MAX_PASSWORD_LEN 100

typedef struct {
    char digits[MAX_WORD_LEN];
    char letters[MAX_WORD_LEN];
} Mapping;

Mapping mappings[] = {
    {"abc", "a"},
    {"def", "b"},
    {"ghi", "c"},
    {"jkl", "d"},
    {"mno", "e"},
    {"pqrs", "f"},
    {"tuv", "g"},
    {"wxyz", "h"}
};

int main() {
    int N;
    scanf("%d", &N);

    char password[MAX_PASSWORD_LEN];
    scanf("%s", password);

    char words[MAX_WORDS][MAX_WORD_LEN];
    for (int i = 0; i < N; i++) {
        scanf("%s", words[i]);
    }

    // Check if the password can be formed using the words in the dictionary
    for (int i = 0; i < N; i++) {
        bool valid = true;
        for (int j = 0; j < strlen(words[i]); j++) {
            char letter = words[i][j];
            bool found = false;
            for (int k = 0; k < sizeof(mappings) / sizeof(mappings[0]); k++) {
                if (strchr(mappings[k].letters, letter) != NULL) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                valid = false;
                break;
            }
        }
        if (valid) {
            printf("%s\n", words[i]);
            return 0;
        }
    }

    printf("No Solutions!\n");
    return 0;
}