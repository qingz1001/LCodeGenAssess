#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 11
#define MAX_ARTICLE_LEN 1000001

void to_lower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int main() {
    char word[MAX_WORD_LEN];
    char article[MAX_ARTICLE_LEN];
    int word_count = 0;
    int first_pos = -1;

    scanf("%s", word);
    getchar(); // consume newline character
    fgets(article, MAX_ARTICLE_LEN, stdin);

    to_lower(word);
    to_lower(article);

    int word_len = strlen(word);
    int article_len = strlen(article);

    for (int i = 0; i <= article_len - word_len; i++) {
        if ((i == 0 || isspace(article[i - 1])) && (i + word_len == article_len || isspace(article[i + word_len]))) {
            if (strncmp(article + i, word, word_len) == 0) {
                word_count++;
                if (first_pos == -1) {
                    first_pos = i;
                }
            }
        }
    }

    if (word_count > 0) {
        printf("%d %d\n", word_count, first_pos);
    } else {
        printf("-1\n");
    }

    return 0;
}