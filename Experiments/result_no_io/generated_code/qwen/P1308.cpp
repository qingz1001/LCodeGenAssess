#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char word[11], text[1000001];
    scanf("%s", word);
    scanf(" %[^\n]", text);

    int count = 0, pos = -1;
    int len_word = strlen(word);
    int len_text = strlen(text);

    for (int i = 0; i <= len_text - len_word; i++) {
        if (isalpha(text[i])) {
            int j;
            for (j = 0; j < len_word; j++) {
                if (tolower(text[i + j]) != tolower(word[j])) break;
            }
            if (j == len_word) {
                if (pos == -1) pos = i;
                count++;
            }
        }
    }

    printf("%d %d\n", count, pos);
    return 0;
}