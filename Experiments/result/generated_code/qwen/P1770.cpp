#include <stdio.h>
#include <string.h>

#define MAX_LEN 1005

void addBoldTag(char *s, const char *keywords[]) {
    int len = strlen(s);
    int keywordCount = 0;
    while (keywords[keywordCount] != NULL) {
        keywordCount++;
    }

    int boldStart[MAX_LEN] = {0};
    int boldEnd[MAX_LEN] = {0};

    for (int i = 0; i < keywordCount; i++) {
        int pos = -1;
        while ((pos = strstr(s + pos + 1, keywords[i])) != NULL) {
            int start = pos - s;
            int end = start + strlen(keywords[i]);
            for (int j = start; j < end; j++) {
                boldStart[j] = 1;
                boldEnd[j] = 1;
            }
        }
    }

    for (int i = 0; i < len; i++) {
        if (boldStart[i]) {
            printf("<b>");
        }
        printf("%c", s[i]);
        if (boldEnd[i]) {
            printf("</b>");
        }
    }
}

int main() {
    char keywords[101][MAX_LEN];
    char query[MAX_LEN];
    char title[MAX_LEN];

    fgets(query, sizeof(query), stdin);
    fgets(title, sizeof(title), stdin);

    // Remove newline characters
    query[strcspn(query, "\n")] = '\0';
    title[strcspn(title, "\n")] = '\0';

    // Tokenize the query into keywords
    int keywordIndex = 0;
    char *token = strtok(query, " ");
    while (token != NULL && keywordIndex < 100) {
        strcpy(keywords[keywordIndex], token);
        keywordIndex++;
        token = strtok(NULL, " ");
    }
    keywords[keywordIndex] = NULL;

    addBoldTag(title, (const char **)keywords);

    return 0;
}