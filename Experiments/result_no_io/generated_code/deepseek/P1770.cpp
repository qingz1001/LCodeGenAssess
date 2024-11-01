#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 10000

void addBoldTag(char *keyword, char *text) {
    int keywordLen = strlen(keyword);
    int textLen = strlen(text);
    bool inBold = false;
    int i, j;

    for (i = 0, j = 0; i < textLen; i++) {
        if (text[i] == ' ') {
            continue;
        }

        int k = 0;
        while (i + k < textLen && text[i + k] == keyword[j + k]) {
            k++;
        }

        if (k > 1) {
            if (!inBold) {
                printf("<b>");
                inBold = true;
            }
            while (k > 0) {
                printf("%c", text[i]);
                i++;
                k--;
            }
            i--;
            j += k;
        } else {
            if (inBold) {
                printf("</b>");
                inBold = false;
            }
            printf("%c", text[i]);
            j++;
        }
    }

    if (inBold) {
        printf("</b>");
    }
}

int main() {
    char keyword[MAX_LEN];
    char text[MAX_LEN];

    fgets(keyword, MAX_LEN, stdin);
    fgets(text, MAX_LEN, stdin);

    // Remove newline characters if present
    keyword[strcspn(keyword, "\n")] = 0;
    text[strcspn(text, "\n")] = 0;

    addBoldTag(keyword, text);

    return 0;
}