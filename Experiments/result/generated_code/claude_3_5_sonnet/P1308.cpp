#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 11
#define MAX_ARTICLE_LENGTH 1000001

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int isWordBoundary(char c) {
    return c == ' ' || c == '\0';
}

int main() {
    char word[MAX_WORD_LENGTH];
    char article[MAX_ARTICLE_LENGTH];
    
    fgets(word, MAX_WORD_LENGTH, stdin);
    word[strcspn(word, "\n")] = 0;
    
    fgets(article, MAX_ARTICLE_LENGTH, stdin);
    article[strcspn(article, "\n")] = 0;
    
    toLowerCase(word);
    toLowerCase(article);
    
    int wordLen = strlen(word);
    int articleLen = strlen(article);
    int count = 0;
    int firstPosition = -1;
    
    for (int i = 0; i <= articleLen - wordLen; i++) {
        if ((i == 0 || isWordBoundary(article[i-1])) &&
            strncmp(article + i, word, wordLen) == 0 &&
            isWordBoundary(article[i + wordLen])) {
            
            count++;
            if (firstPosition == -1) {
                firstPosition = i;
            }
        }
    }
    
    if (count > 0) {
        printf("%d %d\n", count, firstPosition);
    } else {
        printf("-1\n");
    }
    
    return 0;
}