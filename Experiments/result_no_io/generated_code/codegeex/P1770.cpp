#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000

void processKeywords(char *keywords, char *processedKeywords) {
    int len = strlen(keywords);
    for (int i = 0; i < len; i++) {
        if (keywords[i] == ' ') {
            processedKeywords[i] = ' ';
        } else {
            processedKeywords[i] = '<';
            processedKeywords[i + 1] = 'b';
            processedKeywords[i + 2] = '>';
            processedKeywords[i + 3] = keywords[i];
            i += 3;
        }
    }
    processedKeywords[len + 3] = '\0';
}

void processSentence(char *sentence, char *processedSentence, char *processedKeywords) {
    int len1 = strlen(sentence);
    int len2 = strlen(processedKeywords);
    int j = 0;
    for (int i = 0; i < len1; i++) {
        if (sentence[i] == ' ') {
            processedSentence[j++] = ' ';
            i++;
        } else {
            int k;
            for (k = 0; k < len2; k++) {
                if (sentence[i + k] != processedKeywords[k]) {
                    break;
                }
            }
            if (k == len2) {
                processedSentence[j++] = '<';
                processedSentence[j++] = '/';
                processedSentence[j++] = 'b';
                processedSentence[j++] = '>';
                i += k - 1;
            } else {
                processedSentence[j++] = sentence[i];
            }
        }
    }
    processedSentence[j] = '\0';
}

int main() {
    char keywords[MAX_LEN];
    char sentence[MAX_LEN];
    char processedKeywords[MAX_LEN * 4];
    char processedSentence[MAX_LEN * 4];

    fgets(keywords, MAX_LEN, stdin);
    keywords[strcspn(keywords, "\n")] = 0; // Remove newline character
    fgets(sentence, MAX_LEN, stdin);
    sentence[strcspn(sentence, "\n")] = 0; // Remove newline character

    processKeywords(keywords, processedKeywords);
    processSentence(sentence, processedSentence, processedKeywords);

    printf("%s\n", processedSentence);

    return 0;
}