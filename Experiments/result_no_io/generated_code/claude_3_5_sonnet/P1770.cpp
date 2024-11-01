#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEYWORD 1000
#define MAX_TITLE 10000

char keyword[MAX_KEYWORD];
char title[MAX_TITLE];
char result[MAX_TITLE];

int is_word(char *str) {
    int count = 0;
    while (*str) {
        if (*str == ' ') count++;
        str++;
    }
    return count >= 1;
}

void process() {
    char *k = keyword, *t = title, *r = result;
    char word[100], *w;
    int in_bold = 0;

    while (*t) {
        w = word;
        while (*t && *t != ' ' && *t != ',' && *t != '.') {
            *w++ = *t++;
        }
        *w = '\0';

        if (is_word(word)) {
            char *found = strstr(keyword, word);
            if (found && (found == keyword || *(found-1) == ' ') &&
                (*(found+strlen(word)) == ' ' || *(found+strlen(word)) == '\0')) {
                if (!in_bold) {
                    strcpy(r, "<b>");
                    r += 3;
                    in_bold = 1;
                }
            } else {
                if (in_bold) {
                    strcpy(r, "</b>");
                    r += 4;
                    in_bold = 0;
                }
            }
        } else if (in_bold) {
            strcpy(r, "</b>");
            r += 4;
            in_bold = 0;
        }

        strcpy(r, word);
        r += strlen(word);

        if (*t) {
            *r++ = *t++;
        }
    }

    if (in_bold) {
        strcpy(r, "</b>");
    }
}

int main() {
    fgets(keyword, MAX_KEYWORD, stdin);
    fgets(title, MAX_TITLE, stdin);

    keyword[strcspn(keyword, "\n")] = 0;
    title[strcspn(title, "\n")] = 0;

    process();
    printf("%s\n", result);

    return 0;
}