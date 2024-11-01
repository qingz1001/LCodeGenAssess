#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 1005

bool isChineseWord(char *str) {
    return strlen(str) > 1 && str[0] != ' ' && str[1] != ' ';
}

void boldWords(char *keyword, char *sentence) {
    char result[MAX_LEN * 2] = {0};
    char *kw_words[MAX_LEN], *sent_words[MAX_LEN];
    int kw_count = 0, sent_count = 0;

    // Split keyword into words
    char *kw_token = strtok(keyword, " ");
    while (kw_token != NULL) {
        if (isChineseWord(kw_token)) {
            kw_words[kw_count++] = kw_token;
        }
        kw_token = strtok(NULL, " ");
    }

    // Split sentence into words
    char *sent_token = strtok(sentence, " ");
    while (sent_token != NULL) {
        if (isChineseWord(sent_token)) {
            sent_words[sent_count++] = sent_token;
        }
        sent_token = strtok(NULL, " ");
    }

    // Process sentence words
    int i = 0, j = 0;
    while (i < sent_count) {
        bool found = false;
        for (j = 0; j < kw_count; j++) {
            if (strcmp(sent_words[i], kw_words[j]) == 0) {
                found = true;
                break;
            }
        }
        if (found) {
            strcat(result, "<b>");
            strcat(result, sent_words[i]);
            strcat(result, "</b>");
        } else {
            strcat(result, sent_words[i]);
        }
        strcat(result, " ");
        i++;
    }

    printf("%s\n", result);
}

int main() {
    char keyword[MAX_LEN], sentence[MAX_LEN];
    fgets(keyword, MAX_LEN, stdin);
    fgets(sentence, MAX_LEN, stdin);

    // Remove newline characters
    keyword[strcspn(keyword, "\n")] = 0;
    sentence[strcspn(sentence, "\n")] = 0;

    boldWords(keyword, sentence);

    return 0;
}