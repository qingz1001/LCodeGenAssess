#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 1000

int countNames(char *sentence) {
    int count = 0;
    int len = strlen(sentence);
    int isWord = 0;
    int isName = 0;

    for (int i = 0; i < len; i++) {
        if (isalpha(sentence[i])) {
            if (!isWord) {
                isWord = 1;
                isName = isupper(sentence[i]);
            } else if (isupper(sentence[i])) {
                isName = 0;
            }
        } else {
            if (isWord && isName) {
                count++;
            }
            isWord = 0;
            isName = 0;
        }
    }

    return count;
}

int main() {
    int N;
    char input[MAX_LENGTH + 1];
    char sentence[MAX_LENGTH + 1];
    int sentenceStart = 0;

    scanf("%d\n", &N);
    fgets(input, sizeof(input), stdin);

    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == '.' || input[i] == '?' || input[i] == '!') {
            strncpy(sentence, input + sentenceStart, i - sentenceStart + 1);
            sentence[i - sentenceStart + 1] = '\0';
            printf("%d\n", countNames(sentence));
            sentenceStart = i + 2;  // Skip the space after punctuation
        }
    }

    return 0;
}