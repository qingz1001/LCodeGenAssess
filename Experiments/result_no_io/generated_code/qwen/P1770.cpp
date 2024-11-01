#include <stdio.h>
#include <string.h>

#define MAX_LEN 1010

void boldWords(char *keywords, char *question) {
    int lenK = strlen(keywords);
    int lenQ = strlen(question);

    for (int i = 0; i <= lenQ - lenK; i++) {
        if (strncmp(keywords, question + i, lenK) == 0) {
            printf("<b>%s</b>", keywords);
            return;
        }
    }

    printf("%s", keywords);
}

int main() {
    char keywords[MAX_LEN], question[MAX_LEN];

    fgets(keywords, sizeof(keywords), stdin);
    fgets(question, sizeof(question), stdin);

    // Remove newline characters
    keywords[strcspn(keywords, "\n")] = '\0';
    question[strcspn(question, "\n")] = '\0';

    boldWords(keywords, question);

    return 0;
}